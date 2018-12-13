import math
from random import randint
# version 1.0 - v1.1 is being written in C
def pseudogen(str1, str2):
    charnum = {"a": 9,"b": 4,"c": 2,"d": 4,"e": 10,"f": 5,"g": 3,"h": 6,"i": 8,"j": 5,"k": 4,"l": 5,\
    "m": 5,"n": 5,"o": 7,"p": 5,"q": 6,"r": 3,"s": 6,"t": 2,"u": 7,"v": 3,"w": 5,"x": 6,"y": 7,"z": 1,\
    "A": 9,"B": 4,"C": 2,"D": 4,"E": 10,"F": 5,"G": 3,"H": 6,"I": 8,"J": 5,"K": 4,"L": 5,"M": 5,"N": 5,"O": 7,\
    "P": 5,"Q": 6,"R": 3,"S": 6,"T": 2,"U": 7,"V": 3,"W": 5,"X": 6,"Y": 7,"Z": 1,"0": 0,"1": 1,"2": 2,"3": 3,"4": 4,\
    "5": 5,"6": 6,"7": 7,"8": 8,"9": 9," ": 0,"-": 0,}
    for i in charnum:
        charnum[i] -= 5
    facts = ["This generator is psuedorandom - it will return the same answer\nif you add the same input.",
    "Elise and Thomson were shipped 15 times during the testing!",]
    t1 = 0
    t2 = 0
    if not (type(str1) == str and type(str2) == str):
        print ("<invalid: not strings>")
    elif len(str1) > 15 or len(str2) > 15:
        print ("<invalid: too long>")
    elif len(str1) == 0 or len(str2) == 0:
        print ("<invalid: null input>")
    else:
        for i in range(len(str1)):
            if str1[i] in charnum.keys():
                t1 += charnum[str1[i]]
            else:
                print ("<invalid: unstable chars>")
                print ("Female name, char %s" % (i))
                print ("stable: a-z, A-Z, 0-9, (space), (hyphen)")
                return
        a1 = t1 / (len(str1))
        for i in range(len(str2)):
            if str2[i] in charnum.keys():
                t2 += charnum[str2[i]]
            else:
                print ("<invalid: unstable chars>")
                print ("Male name, char %s" % (i))
                print ("stable; a-z, A-Z, 0-9, (space), (hyphen)")
                return
        a2 = t2 / (len(str2))
        calc = str(int(math.floor(\
            (\
                1 - math.sqrt(\
                    math.fabs(a1 - a2) / 10\
                )\
            ) * 100\
        )))
        meter = math.ceil(float(calc)/10)
        print ("[❤-+-❤Matchmaking❤-+-❤]")
        print ("Female: %s" % (str1))
        print ("Male: %s" % (str2))
        print ("Match: %s%%" % (calc))
        print ("Meter: [" + str(meter * "*") + str((10 - meter) * " ") + "]")
        print ("[❤-+-❤Matchmaking❤-+-❤]")
        print ("[❤Fun fact!❤]")
        print (facts[randint(0, len(facts) - 1)])
        print ("[❤-+-❤Matchmaking❤-+-❤]")

while True:
    print ("Enter victim names.")
    in1 = input("Victim 1(female):")
    in2 = input("Victim 2(male):")
    print ("\n\n")
    pseudogen(in1, in2)
    print ("\n\n")
