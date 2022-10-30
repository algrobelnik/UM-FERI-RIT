import matplotlib.pyplot as plt

def izris(slika, crta, tocke, podatki):
    fig, axis = plt.subplots(ncols=2, nrows=2)
    gs = axis[0,0].get_gridspec()
    axis[0, 0].remove()
    axis[0, 1].remove()
    axbig = fig.add_subplot(gs[0, :])
    axbig.imshow(slika)
    axbig.axis("off")
    axbig.set_title("slika")

    a = []
    b = []
    for tocka in tocke:
        a.append(tocka[0])
        b.append(tocka[1])

    ct = axis[1,0]
    ct.plot(crta, color="green", marker="x", linestyle="dashed", label="crta")
    ct.scatter(a, b, color="darkturquoise", marker="+", label="tocke")
    ct.set_title("crta in tocke")
    ct.axis([-1,11,-2,9])
    ct.set_xlabel("index")
    ct.set_ylabel("vrednost")
    ct.legend(loc="upper right")

    po = axis[1,1]
    po.stem(podatki, label="podatki")
    po.set_title("podatki")
    po.axis([-1,11,-2,9])
    po.set_xlabel("A")
    po.set_ylabel("B")
    po.legend(loc="upper left")

    fig.tight_layout()

    return 0

