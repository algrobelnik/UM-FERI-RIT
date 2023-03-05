Simple program that solves following problem:
Gold Bar Robbers
Description: N robbers broke into a bank that stores gold bars in an underground vault. After opening the vault, each robber took a share of the gold bars in sequence.
The first robber divided the gold bars into N shares, then grabbed his share. Because he was greedy, he took one additional leftover bar that wasn't assigned to any share and headed towards the exit. However, the weight of the bars was too much, and one bar fell to the ground and got damaged on his way out.
He left the damaged bar behind because damages reduce the value of the bars.
The remaining gold bars were redistributed by the second robber into N shares again. He grabbed his share of the gold bars, but being greedy, he took one additional leftover bar that wasn't assigned to any share, which, like the first robber, fell on the ground and got damaged. He left the damaged bar behind and headed towards the exit.
The rest of the robbers did the same. The scenario of leaving a damaged bar behind repeated with all of them.
Just before escaping, the robbers noticed that some bars were still in the vault. They agreed to divide them equally among themselves. The robbers completely emptied the vault. This time they were more skillful in carrying the gold bars, and none of them fell on the ground.
We want to find out the maximum possible number of robbers N if we know the number of gold bars G in the vault.
If a solution exists, it is displayed as 'number of gold bars: G - number of robbers: N'. If there is no solution, it is displayed as 'number of gold bars: G - no solution!'

To run this program run:
1. step by step

  if you don't have obj/main.x

```make all```

  if you already have obj/main.x

```make clean all```

  then run program

```./obj/main.x *fileName*```

2. All together

```(make clean all || make all) && ./obj/main.x *fileName*```
