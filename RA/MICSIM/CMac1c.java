package si.unimb.feri.raj.MAC1;

import java.io.*;

/**
 * Primitiven prevajalnik za MAC zbirnegi jeziki (za HO z originalnim interpreterjem).
 *
 *	Razred opravi bijektivno preslikavo mnemonikov in argumentov 
 * @author Simon Tutek 2002
 */
class CMac1c {

	// simbolne tabele (mnemoniki)
	protected final static String strMnemoniki[] = 
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
			"END",
      "MUL"
    };
	// maske argumentov
	protected final static int iArgumentMaske[] =
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
			0x0000,
      0x00FF
    };
			
	// operacijska koda za mnemonike
	protected final static int iOperacijskeKode[] =
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
			0xFFFF,
      0xFD00
    };

	/**
	 * Vstopna točka za prevajalnik.
	 * 
	 * @param args
	 */
	public static void main(String args[]) {

		// TODO Nekega dne bi bilo potrebno to metodo razbiti na več manjših
		 
		int iMem[] = new int[4096];	// slika pomnilnika 
		int iLokacija = 0; 					// mesto instrukcije
		boolean bVerbose = false; 	// ce 3. argument enak '-v' izpisi dodatne informacije

		// preverjanje vhodnih argumentov
		if (args.length < 2) {
			System.out.println(
				"Premalo argumentov (Podajte vhodno in izhodno datoteko)!\n\tUporaba:java asm <vhod> <izhod> [-v]");
			System.exit(-1);
		}

		// preverjanje sledecih argumentov
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
				System.out.println("Neznani argumenti:" + a);
		}

		StreamTokenizer st;
		boolean bData = false;

		try {

			st = new StreamTokenizer(new FileReader(args[0]));
			st.commentChar(';');
			st.eolIsSignificant(true);

			while (st.nextToken() != -1) {

				if (bVerbose)
					System.out.println("Razpoznavam token: " + st.toString());

				// preskočimo prazne vrstice
				if (st.ttype == StreamTokenizer.TT_EOL) {

					if (bVerbose)
						System.out.println("Preskočim vrstico: " + st.lineno());

					continue;
				}

				int iInstrukcija = -1;

				// ************************************************************************************************
				// programski segment
				if (!bData) {

					if (st.ttype != StreamTokenizer.TT_WORD) {
						System.out.println("Neznan ukaz: " + st.toString());
						System.exit(-10);
					}

					if (st.sval.compareToIgnoreCase("DATA") == 0) {

						bData = true;

						if (bVerbose)
							System.out.println("Data: " + st.lineno());

						continue;
					}

					// iskanje mnemonika
					int iIndex = -1;
					for (int i = 0; i < strMnemoniki.length; i++)
						if (strMnemoniki[i].compareToIgnoreCase(st.sval) == 0) {

							iIndex = i;

							if (bVerbose)
								System.out.println(
									"Našel mnemonik: "
										+ strMnemoniki[iIndex]
										+ " v vrstici: "
										+ st.lineno());
							break;
						}

					// neznan ukaz ?
					if (iIndex < 0) {

						System.out.println(
							"NAPAKA: Neznan ukaz "
								+ st.toString()
								+ " (vrstica: "
								+ st.lineno()
								+ ").");
						System.exit(-10);
					}

					iInstrukcija = iOperacijskeKode[iIndex];

					// zahteva argument ?
					if (iArgumentMaske[iIndex] > 0) {

						st.nextToken();

						// ni argumenta ?
						if (st.ttype != StreamTokenizer.TT_NUMBER) {

							System.out.println(
								"NAPAKA: Ukaz "
									+ strMnemoniki[iIndex]
									+ " zahteva argument (vrstica: "
									+ st.lineno()
									+ ").");
							System.exit(-10);
						}

						// overflow
						if ((int) st.nval > iArgumentMaske[iIndex]) {

							System.out.println(
								"NAPAKA: Ukaz "
									+ strMnemoniki[iIndex]
									+ " overflow. Argument > od "
									+ iArgumentMaske[iIndex]
									+ " (vrstica: "
									+ st.lineno()
									+ ").");
							System.exit(-10);
						}

						// izracun instrukcije
						iInstrukcija += (int) st.nval;
					}

					st.nextToken();
					if (st.ttype != StreamTokenizer.TT_EOL) {
						System.out.println(
							"NAPAKA: pričakujem EOL (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}
				}
				// *************************************************************************************
				// data segment
				else {
					// ni naslov ?
					if (st.ttype != StreamTokenizer.TT_NUMBER) {

						System.out.println(
							"NAPAKA: Pričakujem naslov (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}

					// overflow ?
					if (st.nval > 0x0FFF || st.nval < 0) {

						System.out.println("NAPAKA: Naslov (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}

					iLokacija = (int) st.nval;

					// iscemo separator ':'
					st.nextToken();
					if (st.ttype != ':') {
						System.out.println(
							"NAPAKA: Pričakujem separator ':' (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}

					// argument
					st.nextToken();
					if (st.ttype != StreamTokenizer.TT_NUMBER) {

						System.out.println(
							"NAPAKA: Pričakujem argument (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}

					// argument owerflow
					if (st.nval > 0xFFFF) {

						System.out.println(
							"NAPAKA: Argument overflow (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}

					iInstrukcija = (int) st.nval;

					st.nextToken();
					if (st.ttype != StreamTokenizer.TT_EOL) {
						System.out.println(
							"NAPAKA: pričakujem EOL (vrstica: " + st.lineno() + ").");
						System.exit(-10);
					}
				}

				// *********************************************************************************************
				// zapisovanje v mem 
				if (bVerbose)
					System.out.println(
						"Izračunana instrukcija: "
							+ Integer.toHexString(iInstrukcija)
							+ " lokacija: "
							+ iLokacija);

				if (iInstrukcija > 0)
					iMem[iLokacija++] = iInstrukcija;
			}

			// ************************************************************************************************
			// zapisovanje 

			if (bVerbose)
				System.out.println("\n Zapisovanje: ");

			FileOutputStream fos = new FileOutputStream(args[1]);
			for (int i = 0; i < 4096; i++) {

				// kontrolni izpisi
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

				// zapisi
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
