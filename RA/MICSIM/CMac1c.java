package si.unimb.feri.raj.MAC1;

import java.io.*;

/**
 * A primitive compiler for the MAC1 assembly language (for the HO with the original interpreter).
 *
 *	The class makes a bijective translation of mnemonics and arguments
 * @author Simon Tutek 2002; translation to English Ales.Zamuda@UM.SI 2018
 */
class CMac1c {

	// symbol tables (mnemonics)
	protected final static String strMnemonics[] = 
		{
			"LODD",
			"STOD",
			"ADDD",
			"SUBD",
			"JPOS",
			"JZER",
			"JUMP",
			"LOCO",
			"LODL",
			"STOL",
			"ADDL",
			"SUBL",
			"JNEG",
			"JNZE",
			"CALL",
			"PSHI",
			"POPI",
			"PUSH",
			"POP",
			"RETN",
			"SWAP",
			"INSP",
			"DESP",
			"END" };
	// masks of arguments
	protected final static int iArgumentMasks[] =
		{
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0FFF,
			0x0000,
			0x0000,
			0x0000,
			0x0000,
			0x0000,
			0x0000,
			0x00FF,
			0x00FF,
			0x0000 };
			
	// operation code for mnemonics
	protected final static int iOperationCodes[] =
		{
			0x0000,
			0x1000,
			0x2000,
			0x3000,
			0x4000,
			0x5000,
			0x6000,
			0x7000,
			0x8000,
			0x9000,
			0xA000,
			0xB000,
			0xC000,
			0xD000,
			0xE000,
			0xF000,
			0xF200,
			0xF400,
			0xF600,
			0xF800,
			0xFA00,
			0xFC00,
			0xFE00,
			0xFFFF };

	/**
	 * Entry point for the compiler.
	 * 
	 * @param args
	 */
	public static void main(String args[]) {

		// TODO This method could be chunked to smaller code pieces
		 
		int iMem[] = new int[4096];	// memory image
		int iLocation = 0; 					// instruction location
		boolean bVerbose = false; 	// if 3rd argument is same to '-v', print additional information

		// checking input arguments
		if (args.length < 2) {
			System.out.println(
				"Too few arguments (Enter input and output file)!\n\tUsage:java asm <input> <output> [-v]");
			System.exit(-1);
		}

		// checking of arguments that follow
		if (args.length > 2) {

			String a = "";

			if (args[2].compareTo("-v") == 0)
				bVerbose = true;
			else {
				a += " " + args[2];
			}
			for (int i = 3; i < args.length; i++)
				a += " " + args[i];

			if (a.length() > 0)
				System.out.println("Unknown arguments:" + a);
		}

		StreamTokenizer st;
		boolean bData = false;

		try {

			st = new StreamTokenizer(new FileReader(args[0]));
			st.commentChar(';');
			st.eolIsSignificant(true);

			while (st.nextToken() != -1) {

				if (bVerbose)
					System.out.println("Recognizing token: " + st.toString());

				// skip empty lines
				if (st.ttype == StreamTokenizer.TT_EOL) {

					if (bVerbose)
						System.out.println("Skipping line: " + st.lineno());

					continue;
				}

				int iInstruction = -1;

				// ************************************************************************************************
				// program segment
				if (!bData) {

					if (st.ttype != StreamTokenizer.TT_WORD) {
						System.out.println("Unknown command: " + st.toString());
						System.exit(-10);
					}

					if (st.sval.compareToIgnoreCase("DATA") == 0) {

						bData = true;

						if (bVerbose)
							System.out.println("Data: " + st.lineno());

						continue;
					}

					// finding mnemonic
					int iIndex = -1;
					for (int i = 0; i < strMnemonics.length; i++)
						if (strMnemonics[i].compareToIgnoreCase(st.sval) == 0) {

							iIndex = i;

							if (bVerbose)
								System.out.println(
									"Found mnemonic: "
										+ strMnemonics[iIndex]
										+ " in line: "
										+ st.lineno());
							break;
						}

					// unknown operation ?
					if (iIndex < 0) {

						System.out.println(
							"ERROR: Unknown operation "
								+ st.toString()
								+ " (line: "
								+ st.lineno()
								+ ").");
						System.exit(-10);
					}

					iInstruction = iOperationCodes[iIndex];

					// requires argument ?
					if (iArgumentMasks[iIndex] > 0) {

						st.nextToken();

						// ni argumenta ?
						if (st.ttype != StreamTokenizer.TT_NUMBER) {

							System.out.println(
								"ERROR: Operation "
									+ strMnemonics[iIndex]
									+ " requires argument (line: "
									+ st.lineno()
									+ ").");
							System.exit(-10);
						}

						// overflow
						if ((int) st.nval > iArgumentMasks[iIndex]) {

							System.out.println(
								"ERROR: Operation "
									+ strMnemonics[iIndex]
									+ " overflow. Argument > od "
									+ iArgumentMasks[iIndex]
									+ " (line: "
									+ st.lineno()
									+ ").");
							System.exit(-10);
						}

						// compute instruction
						iInstruction += (int) st.nval;
					}

					st.nextToken();
					if (st.ttype != StreamTokenizer.TT_EOL) {
						System.out.println(
							"ERROR: expecting EOL (line: " + st.lineno() + ").");
						System.exit(-10);
					}
				}
				// *************************************************************************************
				// data segment
				else {
					// not address ?
					if (st.ttype != StreamTokenizer.TT_NUMBER) {

						System.out.println(
							"ERROR: Expecting address (line: " + st.lineno() + ").");
						System.exit(-10);
					}

					// overflow ?
					if (st.nval > 0x0FFF || st.nval < 0) {

						System.out.println("ERROR: Address (line: " + st.lineno() + ").");
						System.exit(-10);
					}

					iLocation = (int) st.nval;

					// find separator ':'
					st.nextToken();
					if (st.ttype != ':') {
						System.out.println(
							"ERROR: Expecting separator ':' (line: " + st.lineno() + ").");
						System.exit(-10);
					}

					// argument
					st.nextToken();
					if (st.ttype != StreamTokenizer.TT_NUMBER) {

						System.out.println(
							"ERROR: Expecting argument (line: " + st.lineno() + ").");
						System.exit(-10);
					}

					// argument owerflow
					if (st.nval > 0xFFFF) {

						System.out.println(
							"ERROR: Argument overflow (line: " + st.lineno() + ").");
						System.exit(-10);
					}

					iInstruction = (int) st.nval;

					st.nextToken();
					if (st.ttype != StreamTokenizer.TT_EOL) {
						System.out.println(
							"ERROR: Expecting EOL (line: " + st.lineno() + ").");
						System.exit(-10);
					}
				}

				// *********************************************************************************************
				// writing to mem
				if (bVerbose)
					System.out.println(
						"Computed instruction: "
							+ Integer.toHexString(iInstruction)
							+ " location: "
							+ iLocation);

				if (iInstruction > 0)
					iMem[iLocation++] = iInstruction;
			}

			// ************************************************************************************************
			// writing 

			if (bVerbose)
				System.out.println("\n Writing: ");

			FileOutputStream fos = new FileOutputStream(args[1]);
			for (int i = 0; i < 4096; i++) {

				// control prints
				if (bVerbose && iMem[i] != 0) {
					String s1 = Integer.toHexString((iMem[i] & 0xFF00) >> 8);
					String s2 = Integer.toHexString(iMem[i] & 0x00FF);

					if (s1.length() < 2)
						s1 = "0" + s1;
					if (s2.length() < 2)
						s2 = "0" + s2;

					System.out.println(
						i
							+ ":\t"
							+ s1
							+ " "
							+ s2
							+ "\tamask: "
							+ (iMem[i] & 0x0FFF)
							+ "\tsmask: "
							+ (iMem[i] & 0x00FF));
				}

				// writing
				fos.write(iMem[i] & 0x00FF);
				fos.write((iMem[i] & 0xFF00) >> 8);
			}
			fos.close();
		}
		catch (Exception e) {
			System.out.println(e.toString());
		}
	}
}

