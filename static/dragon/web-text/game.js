(() => {
  const output = document.getElementById("output");
  const form = document.getElementById("form");
  const commandInput = document.getElementById("command");
  const submitBtn = document.getElementById("submit");

  const N = Array(35).fill(0);
  const S = Array(35).fill(0);
  const E = Array(35).fill(0);
  const W = Array(35).fill(0);
  const OB = Array(8).fill(0);
  const RD = Array(35).fill(0);

  let R = 1;
  let DES = "";
  let TC = 0;
  let gameOver = false;

  const data = [
    [0, 6, 2, 0],
    [0, 0, 3, 1],
    [0, 0, 4, 2],
    [0, 0, 5, 3],
    [0, 10, 0, 4],
    [1, 11, 0, 0],
    [0, 0, 8, 0],
    [0, 12, 9, 7],
    [0, 0, 0, 8],
    [5, 14, 0, 0],
    [6, 0, 12, 0],
    [8, 0, 13, 11],
    [0, 0, 14, 12],
    [10, 0, 0, 13],
    [0, 19, 16, 0],
    [0, 0, 17, 15],
    [0, 0, 18, 16],
    [0, 0, 0, 17],
    [15, 20, 0, 0],
    [19, 21, 0, 0],
    [20, 22, 0, 0],
    [21, 26, 23, 0],
    [0, 27, 24, 22],
    [0, 29, 0, 23],
    [0, 30, 0, 0],
    [22, 31, 27, 0],
    [23, 0, 28, 26],
    [0, 0, 0, 0],
    [24, 0, 30, 28],
    [25, 33, 0, 29],
    [26, 0, 0, 0],
    [28, 29, 0, 0],
    [30, 0, 0, 0]
  ];

  function initMap() {
    for (let i = 1; i <= 33; i += 1) {
      const [n, s, e, w] = data[i - 1];
      N[i] = n;
      S[i] = s;
      E[i] = e;
      W[i] = w;
      RD[i] = 0;
    }
    OB[1] = 5;
    OB[2] = 22;
    OB[3] = 25;
    OB[4] = 31;
    OB[5] = 27;
    OB[6] = 33;
    OB[7] = 32;
  }

  function clearScreen() {
    output.textContent = "";
  }

  function print(line = "") {
    output.textContent += `${line}\n`;
    output.scrollTop = output.scrollHeight;
  }

  function printLines(lines) {
    lines.forEach((line) => print(line));
  }

  function promptLine() {
    print("");
    print("WHAT NOW?");
  }

  function gameOverNow() {
    print("");
    print("AUF WIEDERSEHEN (GAME OVER)");
    gameOver = true;
    commandInput.disabled = true;
    submitBtn.disabled = true;
  }

  function listObjectsHere(room) {
    let found = false;
    if (room === OB[1]) { print("- A STICK"); found = true; }
    if (room === OB[2]) { print("- A SWORD"); found = true; }
    if (room === OB[3]) { print("- A MAGIC SPRING"); found = true; }
    if (room === OB[4]) { print("- A DRUMSTICK"); found = true; }
    if (room === OB[5]) { print("- A MCRIB SANDWICH"); found = true; }
    if (room === OB[6]) { print("- A TOY DRUM"); found = true; }
    if (room === OB[7]) { print("- A DRAGON WAGON"); found = true; }
    if (!found) { print("- NOTHING"); }
    print("");
  }

  function showExits() {
    print("EXITS: ");
    print("");
    let exits = "";
    if (N[R] > 0) exits += "- NORTH;";
    if (S[R] > 0) exits += "- SOUTH;";
    if (E[R] > 0) exits += "- EAST;";
    if (W[R] > 0) exits += "- WEST;";
    let ar = exits.split(";");
    ar.forEach((val, index) => {
      print(ar[index]);
    });
    //print(exits.trimEnd());
  }

  function describeRoom() {
    if (R <= 19) {
      describeRoomSet1(R);
    } else {
      describeRoomSet2(R - 19);
    }
  }

  function showRoom() {
    clearScreen();
    describeRoom();
    print("");
    print("OBJECTS HERE ARE:");
    print("");
    listObjectsHere(R);
    showExits();
    promptLine();
  }

  function showCurrentDescriptionLineOnly() {
    clearScreen();
    print(DES);
  }

  function parseInput(input) {
    const cleaned = input.trim().toUpperCase();
    if (!cleaned) {
      showRoom();
      return;
    }

    let verb = cleaned;
    let noun = "";

    const spaceIndex = cleaned.indexOf(" ");
    if (spaceIndex !== -1) {
      verb = cleaned.slice(0, spaceIndex);
      noun = cleaned.slice(spaceIndex + 1).trim();
    }

    showCurrentDescriptionLineOnly();

    if (verb === "GO") {
      verb = noun;
      noun = "";
      movePlayer(verb);
      return;
    }

    if (["NORTH", "N", "SOUTH", "S", "EAST", "E", "WEST", "W"].includes(verb)) {
      movePlayer(verb);
      return;
    }

    if (["INVENTORY", "INV", "I"].includes(verb)) {
      showInventory();
      return;
    }

    if (["GET", "TAKE"].includes(verb)) {
      getObject(noun);
      return;
    }

    if (["PUSH", "PRESS"].includes(verb)) {
      pressObject(verb, noun);
      return;
    }

    if (verb === "DROP") {
      dropObject(noun);
      return;
    }

    if (verb === "QUIT") {
      gameOverNow();
      return;
    }

    if (["HIT", "STRIKE", "BEAT", "KILL"].includes(verb)) {
      hitSomething(verb, noun);
      return;
    }

    if (verb === "EAT") {
      eatSomething(noun);
      promptLine();
      return;
    }

    if (["FEED", "GIVE"].includes(verb)) {
      feedSomething(verb, noun);
      return;
    }

    if (verb === "DANCE") {
      dance();
      return;
    }

    if (verb === "LOOK") {
      RD[R] = 0;
      showRoom();
      return;
    }

    print("");
    print(`I DON'T KNOW HOW TO ${verb}.`);
    promptLine();
  }

  function movePlayer(verb) {
    const prev = R;
    if (verb === "NORTH" || verb === "N") R = N[R];
    if (verb === "SOUTH" || verb === "S") R = S[R];
    if (verb === "EAST" || verb === "E") R = E[R];
    if (verb === "WEST" || verb === "W") R = W[R];

    if (prev === 28 && R === 32) {
      showRoom();
      return;
    }
    if (R === 28 && S[28] === 32) {
      dragonReenter();
      return;
    }
    if (prev === 28) {
      trappedInDragon();
      return;
    }

    if (R > 0) {
      showRoom();
      return;
    }

    print("");
    print("YOU CAN'T MOVE THAT WAY (I THINK).");
    R = prev;
    promptLine();
  }

  function showInventory() {
    print("");
    print("YOU ARE CARRYING: ");
    print("");
    listObjectsHere(34);
    promptLine();
  }

  function checkNoun(noun) {
    if (!noun) return 0;
    if (noun === "STICK") return 1;
    if (noun === "SWORD") return 2;
    if (noun === "SPRING") return 3;
    if (noun === "DRUMSTICK") return 4;
    if (noun === "MCRIB" || noun === "SANDWICH") return 5;
    if (noun === "DRUM") return 6;
    if (noun === "WAGON") return 7;
    return 0;
  }

  function getObject(noun) {
    if (!noun) {
      print("");
      print("DON'T BE SILLY, I NEED A NOUN!");
      promptLine();
      return;
    }
    const obj = checkNoun(noun);
    if (obj === 0) {
      print("BE REALISTIC.");
      promptLine();
      return;
    }
    if (OB[obj] !== R && OB[obj] !== 34) {
      print("");
      print("YOU CAN'T, AT THE MOMENT.");
      print("");
      promptLine();
      return;
    }
    if (obj === 3 && OB[7] < 34) {
      print("");
      print("YOU CAN'T SEEM TO MOVE THE HEAVY SPRING.");
      print("");
      promptLine();
      return;
    }

    OB[obj] = 34;
    if (OB[3] === 34) {
      print("");
      print("YOU PUSH AND TUG THE MAGIC METAL SPRING INTO THE WAGON");
      print("AND  FIND THAT YOU CAN NOW TRANSPORT IT.");
      print("AREN'T YOU CLEVER, YOU RASCAL YOU.");
      print("");
      promptLine();
      return;
    }

    print("");
    print(`YOU'VE GOT THE ${noun}.`);
    print("");
    promptLine();
  }

  function pressObject(verb, noun) {
    if (!noun) {
      print("");
      print("DON'T BE SILLY, I NEED A NOUN!");
      promptLine();
      return;
    }
    if (R === 11 || R === 18) {
      if (R === 18) {
        if (noun === "ROCK" || noun === "STONE") {
          print("");
          print("YOU PUSH AGAINST IT WITH ALL YOUR MIGHT BUT NOTHING SEEMS TO HAPPEN.");
          print("");
          promptLine();
          return;
        }
        print("");
        print(`I CAN'T ${verb} A ${noun}.`);
        print("");
        promptLine();
        return;
      }
      if (OB[1] === 34) {
        print("");
        print("I'LL PRESS THE BUTTON WITH YOUR STICK SO THE BRIDGE WILL DROP.");
        print("");
        print("OOPS, I'VE DROPPED THE STICK INTO THE RIVER");
        OB[1] = 0;
        S[11] = 15;
        promptLine();
        return;
      }
      if (noun === "BUTTON") {
        print("");
        print("YOU LEAP HIGH IN THE AIR AND PRESS THE BUTTON WITH YOUR HAND.");
        print("THE POISONED LIZARD LIVING ");
        print("");
        print("IN THE BUTTONHOLE ");
        print("PRESSES YOUR HAND WITH ITS FANGS AND...");
        gameOverNow();
        return;
      }
      print("");
      print(`WHOEVER HEARD OF PRESSING A BUTTON WITH A ${noun}?`);
      print("");
      promptLine();
      return;
    }
    print("");
    print(`I CAN'T ${verb} A ${noun}.`);
    print("");
    promptLine();
  }

  function dropObject(noun) {
    const obj = checkNoun(noun);
    if (obj === 0) {
      print("BE REALISTIC.");
      promptLine();
      return;
    }
    if (OB[obj] !== 34) {
      print("");
      print(`I'M NOT CARRYING THE ${noun}.`);
      print("");
      promptLine();
      return;
    }
    OB[obj] = R;
    if (noun === "WAGON" && OB[7] === R) {
      OB[3] = R;
      print("");
      print("OH, OH, WITHOUT HAVING THE WAGON THE HEAVY METAL SPRING TUMBLES TO THE FLOOR.");
      print("");
      if (R === 28) {
        OB[obj] = 0;
        dragonEats(noun);
        return;
      }
      print("");
      print(`I'VE DROPPED THE ${noun}.`);
      print("");
      promptLine();
      return;
    }
    print("");
    print(`I'VE DROPPED THE ${noun}.`);
    print("");
    if (R === 28 && OB[obj] === 28) {
      OB[obj] = 0;
      dragonEats(noun);
      return;
    }
    promptLine();
  }

  function dance() {
    print("");
    print("YOU START TO HUM A CATCHY LITTLE TUNE.");
    print("YOU GRACEFULLY LEAP UP IN THE AIR, DO A PIROUETTE,");
    print("LAND, DO A CARTWHEEL, AND TAKE A BOW.");
    if (R === 28) {
      print("");
      print("THE DRAGON LOOKS AT YOU IN DISGUST. HE GETS UP AND SAYS, ");
      print("'THAT'S AWFUL. THIS IS HOW YOU DO IT.'");
      print("HE IS EXTREMELY CLUMSY AND SAYS,");
      print("'I JUST CAN'T SEEM TO GET THE TEMPO RIGHT.'");
      print("");
      print("HE IS GETTING MADDER AND MADDER. HE LOOKS AT YOU, SNARLS, AND SAYS, ");
      print("'WELL, IF YOU WON'T HELP ME.....'CHOMP!!");
      gameOverNow();
      return;
    }
    print("");
    print("FURRY LITTLE CREATURES APPEAR, APPLAUD FURRIOUSLY, AND LEAVE.");
    promptLine();
  }

  function hitSomething(verb, noun) {
    if (!noun) {
      print("");
      print(`OKAY, BUT YOU HAVE TO TELL ME WHAT IT IS YOU WANT TO ${verb}.`);
      print("");
      promptLine();
      return;
    }
    if (R === 9 && OB[7] < 34) {
      print("");
      print(`WHAT, YOU DARE TO ${verb} IN THE PRESENCE OF THE KING?`);
      print("THE GUARDS SEIZE YOU AND DRAG YOU OFF");
      print("KICKING AND SCREAMING TO BE FED TO THE DRAGON.");
      print("");
      gameOverNow();
      return;
    }
    if (R === 18 && OB[2] === 34) {
      if (noun === "KETTLE") {
        print("");
        print(`YOU ${verb} THE SWORD AGAINST THE KETTLE.`);
        print("THE ROCK VIBRATES IN TUNE AND ROLLS ASIDE,");
        print("REVEALING A PASSAGE TO THE NORTH.");
        N[18] = 14;
        S[14] = 18;
        promptLine();
        return;
      }
      print("YOU " + verb + " THE SWORD AGAINST THE ");
      print(`${noun} BUT NOTHING HAPPENS.`);
      promptLine();
      return;
    }
    if (R === 18) {
      print("");
      print(`YOU ${verb} IT WITH YOUR HAND.`);
      print("");
      print("NOTHING SEEMS TO HAPPEN EXCEPT YOUR HAND HURTS.");
      promptLine();
      return;
    }
    if (noun === "DRUM" || noun === "DRUMSTICK") {
      beatDrum();
      return;
    }
    if (R === 28 && OB[2] === 34) {
      print("");
      print("YOU WHIP OUT YOUR TRUSTY SWORD AND LUNGE.");
      print("");
      print("THE DRAGON LOOKS AT YOU AND SAYS: ");
      print("HOW THOUGHTFUL, HE BROUGHT HIS OWN TOOTHPICK.'");
      print("");
      print(".......CHOMP!!!!");
      gameOverNow();
      return;
    }
    if (R === 28) {
      print("");
      print("YOU ATTACK THE DRAGON FURIOUSLY WITH YOUR BARE HANDS.");
      print("THE DRAGON CHUCKLES AT YOU...");
      print("");
      print("'IF YOU HAD A MAGIC SWORD YOU MIGHT HAVE HAD A CHANCE.'");
      print("");
      print("........CHOMP!!!!");
      gameOverNow();
      return;
    }
    print("");
    print(`YOU CAN'T ${verb} A ${noun} HERE.`);
    promptLine();
  }

  function beatDrum() {
    if (OB[4] === 34 && OB[6] === 34) {
      if (R === 28) {
        print("");
        print("WOW!!! THE DRAGON IS FASCINATED.");
        print("HE GETS UP, TAKES THE DRUM AND DRUMSTICK, ");
        print("SNIFFS IT, AND BEGINS TO DANCE ");
        print("AND BEAT THE DRUMP IN 3/4 TIME.");
        print("");
        print("WHILE HE'S SO OCCUPIED, YOU NOTICE HE HAS MOVED AWAY FROM A PASSAGE TO THE SOUTH.");
        S[28] = 32;
        promptLine();
        return;
      }
      print("");
      print("KABOOM, KABOOM. HITTING THE DRUM WITH THE DRUMSTICK PRODUCES A NICE BEAT.");
      print(" YOU'RE NO GENE KRUPA (WHO?), BUT YOU'LL DO IN A PINCH.");
      promptLine();
      return;
    }
    if (OB[4] !== 34 && OB[6] !== 34) {
      print("YOU DON'T HAVE THAT.");
      promptLine();
      return;
    }
    if (OB[4] === 34) {
      print("");
      print("PERHAPS IF YOU HAD A DRUM...");
      promptLine();
      return;
    }
    if (OB[6] === 34) {
      print("");
      print("YOU HIT THE DRUM WITH YOUR HAND AND PRODUCE A MUFFLED THUD.");
      promptLine();
    }
  }

  function eatSomething(noun) {
    if (!noun) {
      print("");
      print("TSK, TSK, PLEASE SUPPLY A NOUN.");
      return;
    }
    if ((noun === "SANDWICH" || noun === "MCRIB") && OB[5] === 34) {
      print("");
      print("YUM, YUM, THAT TASTED GOOD.");
      OB[5] = 0;
      return;
    }
    if (noun === "SANDWICH" || noun === "MCRIB") {
      print("");
      print("YOU DON'T HAVE IT.");
      return;
    }
    if (noun === "DRUMSTICK" && OB[4] === 34) {
      print("");
      print("YUCK, THAT TASTED AWFUL.");
      OB[4] = 0;
      return;
    }
    if (noun === "DRUMSTICK") {
      print("");
      print("HOW CAN YOU, YOU DON'T HAVE IT.");
      return;
    }
    print("");
    print("DON'T BE SILLY. YOU CAN'T EAT THAT!");
  }

  function feedSomething(verb, noun) {
    const obj = checkNoun(noun);
    if (obj === 0) {
      print("BE REALISTIC");
      promptLine();
      return;
    }
    if (OB[obj] !== 34) {
      print("");
      print(`YOU CAN'T ${verb} SOMETHING YOU`);
      print("DON'T HAVE!");
      promptLine();
      return;
    }
    if (R === 28) {
      OB[obj] = 0;
      dragonEats(noun);
      return;
    }
    print("");
    print("I DON'T KNOW HOW TO TELL YOU THIS, BUT NO ONE WANTS IT.");
    promptLine();
  }

  function dragonEats(noun) {
    print("");
    print(`THE DRAGON GOBBLES UP THE ${noun}.`);
    print("");
    print("'YUMMY, GOOD! WHAT (OR WHO) IS NEXT?'");
    promptLine();
  }

  function trappedInDragon() {
    R = 28;
    print("");
    print("YOU'RE TRAPPED IN THE DRAGON'S CAVE.");
    print("IF YOU DON'T DO SOMETHING SOON YOU'RE IN BIG TROUBLE.");
    TC += 1;
    print("");
    print(`YOU'VE ONLY GOT ${5 - TC} MINUTES LEFT.`);
    if (TC < 5) {
      promptLine();
      return;
    }
    print("");
    print("OH, NO...THE DRAGON'S GETTING UP.");
    print("");
    print("HE'S ");
    print("GOING TO ....CHOMP!!!!");
    gameOverNow();
  }

  function dragonReenter() {
    print("");
    print("THE DRAGON NOTICES YOU REENTER.");
    print("");
    print("'MY, THAT WAS A NICE DANCE. NOW, I'M HUNGRY!'");
    print("");
    print("........CHOMP!!!!");
    gameOverNow();
  }

  function describeRoomSet1(room) {
    switch (room) {
      case 1:
        DES = "YOU ARE IN A FOREST";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("IT IS A WARM SPRING DAY IN THE FOREST PRIMEVAL.");
        print("YOU ARE DRESSED IN A JERKIN.");
        print("CUTE LITTLE FURRY CREATURES BOUND THROUGH THE WOODS.");
        RD[R] = 1;
        return;
      case 2:
        DES = "YOU ARE IN A LEAFY FOREST";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THE LEAVES IN THE TREES ARE QUITE UNUSUAL SINCE THIS IS SPRING.");
        print("");
        print("THESE ARE LEAF SPRINGS.");
        RD[R] = 1;
        return;
      case 3:
        DES = "YOU ARE IN A LEAFY GLADE";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("AREN'T YOU GLAD YOU'RE IN THE GLADE?");
        RD[R] = 1;
        return;
      case 4:
        DES = "YOU ARE IN THE PINE FOREST";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THE WIND BLOWING THROUGH THE PINES IS SINGING A SONG.");
        print("YOU LISTEN CLOSELY AND CAN MAKE OUT SOME OF THE WORDS.");
        print("");
        print("THEY ARE, **I OPINE A DRAGON TO SWEETEN MAKE SURE THAT HE'S EATEN**.");
        RD[R] = 1;
        return;
      case 5:
        DES = "ALL THE TREES ARE DEAD HERE";
        print(DES);
        if (RD[R] === 1) return;
        RD[R] = 1;
        return;
      case 6:
        DES = "YOU ARE ON A PAVED ROAD";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("TO THE SOUTH IS THE NORTH SIDE OF A DRAWBRIDGE.");
        print("THE BRIDGE LOOKS PRETTY RICKETY.");
        RD[R] = 1;
        return;
      case 7:
        DES = "YOU ARE IN THE THRONE ROOM";
        print(DES);
        throneRoom();
        return;
      case 8:
        DES = "YOU ARE IN THE ANTECHAMBER";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THIS, AS YOU'LL FIND, IS NOT A VERY LARGE CASTLE.");
        print("IN FACT IT HAS ONLY THREE (I THINK) ROOMS.");
        RD[R] = 1;
        return;
      case 9:
        DES = "THIS IS THE KING'S BEDROOM";
        print(DES);
        if (OB[3] === 34) {
          print("");
          print("THE ROOM IS EMPTY.");
          return;
        }
        print("");
        print("THE POOR KING HAS BEEN EXPOSED TO WEREWOLF SIMPLEX II");
        print("AND IS SLOWLY TURNING INTO A WOLF.");
        print("");
        print("HE EXPLAINS THAT UNLESS CURED BY THE MAGIC SPRING ");
        print("HE IS DOOMED SINCE HE CAN'T LEAVE THE PALACE.");
        RD[R] = 1;
        return;
      case 10:
        DES = "MORE FOREST";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("JUST MORE AND MORE FOREST");
        RD[R] = 1;
        return;
      case 11:
        DES = "NORTH END OF BRIDGE";
        print(DES);
        drawbridge();
        return;
      case 12:
        DES = "CAUSEWAY TO CASTLE";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("TO THE NORTH YOU SEE A SMALL CASTLE. SMALL DOES NOT DO IT JUSTICE.");
        print("IT IS REALLY SMALL. IF YOU WANT TO SEE HOW SMALL, GO NORTH.");
        RD[R] = 1;
        return;
      case 13:
        DES = "AND YET EVEN MORE FOREST";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("IF YOU THINK IT'S DULL READING ABOUT THE FOREST,");
        print("YOU SHOULD TRY YOUR HAND AT WRITING ABOUT IT.");
        RD[R] = 1;
        return;
      case 14:
        DES = "DARK FOREST";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THERE IS SOMETHING VERY STRANGE HERE.");
        print("THE GROUND SOUNDS HOLLOW!");
        RD[R] = 1;
        return;
      case 15:
        DES = "SOUTH SIDE OF DRAWBRIDGE.";
        print(DES);
        if (RD[R] === 1) return;
        drawbridgeSouth();
        return;
      case 16:
        DES = "GENTLY ROLLING HILLS";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THE HILLS ARE ALIVE WITH THE SOUND OF MUSIC. THEY SING:");
        print("");
        print(" > DON'T PUT YOUR SHOULDER");
        print(" > TO THE BOULDER,");
        print(" > BUT TEST YOUR METTLE,");
        print(" > AGAINST THE KETTLE.");
        RD[R] = 1;
        return;
      case 17:
        DES = "VOLCANIC HIGHLANDS";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("ALL ADVENTURE GAMES HAVE TO HAVE AT LEAST ONE VOLCANO.");
        print("THIS VOLCANO IS ALL POOPED OUT AND");
        print("WILL NOT ERUPT DURING THIS GAME.");
        RD[R] = 1;
        return;
      case 18:
        DES = "VOLCANO VALLEY";
        print(DES);
        if (N[18] === 14) return;
        volcanoRock();
        return;
      case 19:
        DES = "MARSHY SWAMP";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("A SMALL DINOSAUR STICKS ITS TONGUE OUT AT YOU ");
        print("FROM BEHIND A FERN. IT THEN DARTS AWAY.");
        RD[R] = 1;
        return;
      default:
        return;
    }
  }

  function describeRoomSet2(room) {
    switch (room) {
      case 1:
        DES = "MORE MARSHY SWAMP";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THE SMALL DINOSAUR REAPPEARS AND HURLS A ROCK AT YOU.");
        print("THE ROCK MISSES AND THE DINOSAUR DARTS ");
        print("AWAY.");
        RD[R] = 1;
        return;
      case 2:
        DES = "MUSHY SWAMP";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THE SMALL DINOSAUR TAUNTS YOU BY SAYING (IN DINOSAUR LANGUAGE):");
        print("");
        print("'NYAH, NYAH, THE DRAGON'S GONNA GET YOU!'");
        RD[R] = 1;
        return;
      case 3:
        DES = "A PLAIN";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("OUTSIDE OF A RUSTY SWORD, THERE IS NOTHING UNUSUAL HERE.");
        RD[R] = 1;
        return;
      case 4:
        DES = "PLAIN PLAIN";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("NOTHING UNUSUAL HERE.");
        RD[R] = 1;
        return;
      case 5:
        DES = "PLANE PLAIN PLAIN";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("NOT ONLY IS NOTHING UNUSUAL HERE, BUT IT'S VERY FLAT HERE.");
        RD[R] = 1;
        return;
      case 6:
        DES = "THE LAND OF THE MAGIC SPRING";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("A GORGEOUS RAINBOW ARCHES ACROSS THE SKY AND PINK EGRETS FLAP HAPPILY BY.");
        print("A SIGN PAINTED ON THE WALL SAYS:");
        print("'SATISFACTION GUARANTEED OR YOUR MONEY BACK!'");
        RD[R] = 1;
        return;
      case 7:
        DES = "NONDESCRIPT LAND";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("I SIMPLY CAN'T DESCRIBE A NONDESCRIPT LAND.");
        RD[R] = 1;
        return;
      case 8:
        DES = "BREAK LAND";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("LOOKING AROUND YOU SEE PICNIC TABLES AND GARBAGE CANS OVERFLOWING WITH LITTER.");
        print("HOWEVER, IT APPEARS THAT YOU FRIGHTENED SOMEONE OR SOMETHING AWAY");
        print("AS THEY LEFT THEIR LUNCH ON THE TABLE.");
        RD[R] = 1;
        return;
      case 9:
        DES = "LAIR OF THE DRAGON";
        print(DES);
        dragonLair();
        return;
      case 10:
        DES = "TWISTY LITTLE MAZES";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("JUST KIDDING. NO MAZES IN THIS GAME.");
        print("IF YOU WANT TO SEE MY FEELING ON MAZES");
        print("SEE THE LAST ISSUE OF 'SOFTLINE'.");
        RD[R] = 1;
        return;
      case 11:
        DES = "ENTRANCE TO MAGIC LAND";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("MAGIC LAND IS TOO GORGEOUS FOR WORDS.");
        RD[R] = 1;
        return;
      case 12:
        DES = "COLONEL'S CAVERN";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("THIS APPEARS TO HAVE BEEN SOME SORT OF QUICK FOOD PLACE AT ONE TIME.");
        print("THERE IS THE SMELL OF GREASE IN THE AIR.");
        RD[R] = 1;
        return;
      case 13:
        DES = "VERY SECRET CAVE";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("SOMEONE HAS SPRAY PAINTED THIS CAVE AND SCRAWLED GRAFFITI ALL OVER THE WALL.");
        print("I WON'T GIVE ANY MORE DETAILS AS I'M NOT THAT SORT OF COMPUTER.");
        RD[R] = 1;
        return;
      case 14:
        DES = "BOOM BOOM ROOM";
        print(DES);
        if (RD[R] === 1) return;
        print("");
        print("ISN'T THAT RICH?");
        RD[R] = 1;
        return;
      default:
        return;
    }
  }

  function drawbridge() {
    if (S[11] === 15) {
      print("");
      print("THE BRIDGE IS DOWN.");
      print("");
      print("A SIGN UNDER THE BUTTON SAYS:");
      print("'UNDER NO CIRCUMSTANCES PUSH THIS BUTTON!'");
      return;
    }
    print("");
    print("THE BRIDGE IS UP BUT THERE IS A LARGE BUTTON JUST OUT OF YOUR REACH.");
    print("");
    print("A SIGN UNDER THE BUTTON SAYS:");
    print("'UNDER NO CIRCUMSTANCES PUSH THIS BUTTON!'");
  }

  function drawbridgeSouth() {
    print("");
    print("AS YOU PASS OVER THE DRAWBRIDGE");
    print("A THREE-TOED OGRE RUNS FROM UNDER THE BRIDGE CARRYING YOUR STICK.");
    print("HE PRESSES THE BUTTON, CATCHES THE POISONED LIZARD FROM THE BUTTONHOLE ");
    print("AND EATS IT.");
    print("");
    print("THE BRIDGE RAISES HIGH UP IN THE AIR, MAKING IT IMPOSSIBLE TO RETURN.");
    RD[R] = 1;
  }

  function throneRoom() {
    if (OB[7] === 34 && OB[3] === 34) {
      print("");
      print("THE KING JUMPS UP AND DOWN ON THE MAGIC SPRING ");
      print("WHICH ACTIVATES ITS CURATIVE POWERS. HE IS CURED. ");
      print("");
      print("TO SHOW HIS GRATITUDE HE GIVES YOU THE DUSTY TAPESTRY,");
      print("A DEED TO THE DRAGON'S CAVE,");
      print("AND THE TAX BILL THAT THE DRAGON NEVER GOT AROUND TO PAYING");
      print("ON THAT PARTICULAR PIECE OF PROPERTY.");
      print("");
      print("HE ALSO GIVES YOU A COMMISSION FOR A MUCH MORE LUCRATIVE QUEST,");
      print("BUT THAT IS ANOTHER ADVENTURE FOR ANOTHER TIME.");
      gameOverNow();
      return;
    }
    print("");
    print("THE THRONE ROOM IS EMPTY AND FAIRLY CLEAN");
    print("EXCEPT FOR A DUSTY TAPESTRY ON THE WALL. ");
    print("THE TAPESTRY DEPICTS A DRAGON IN A CAVE EATING A MCRIB SANDWICH.");
  }

  function volcanoRock() {
    print("");
    print("YOU ARE IN A WEIRD VALLEY.");
    print("BLOCKING THE NORTH SIDE OF THE CLIFF IS A HUGE ROCK.");
    print("THE ROCK IS CHIPPED AND PRETTY");
    print("WELL BEATEN UP AND DENTED.");
    print("");
    print("A DENTED WITCH'S KETTLE IS BOLTED DOWN HERE.");
  }

  function dragonLair() {
    print("");
    print("A HUGE, FIERCE, HUNGRY RED DRAGON GETS UP FROM ITS NEST IN THE MIDDLE OF THE CAVE.");
    print("");
    print("IT SNORTS FIRE FROM ITS NOSTRILS, BURPS, DOES A BIT OF THE OLD SOFT SHOE, AND SAYS TO YOU:");
    print("");
    print("'BOY I'M GLAD YOU MADE IT. NOT ONLY AM I BORED, BUT I'M STARVING.");
    print("SHALL WE DANCE, OR SHALL YOU FEED ME FIRST?'");
  }

  form.addEventListener("submit", (event) => {
    event.preventDefault();
    if (gameOver) return;
    const input = commandInput.value;
    commandInput.value = "";
    parseInput(input);
  });

  initMap();
  showRoom();
  commandInput.focus();
})();
