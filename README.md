1. [Feladat .............................................................................................................................. 1](#_page0_x68.00_y659.92)
2. [Terv .................................................................................................................................. 2](#_page1_x68.00_y580.92)
3. [Objektum terv ............................................................................................................... 2](#_page1_x68.00_y611.92)
4. [Algoritmusok ................................................................................................................ 4](#_page3_x68.00_y71.92)

[4.1. Tartományon kívüli elemek lekérése ........................................................................ 4](#_page3_x68.00_y96.92)

5. [Megjegyzés a tervhez ....................................................................................................... 4](#_page3_x68.00_y230.92)
1. **Feladat<a name="_page0_x68.00_y659.92"></a>**  

Tervezzen  objektummodellt  kígyójáték  objektumainak  leírására!  Legyen  pálya,  kígyó, gyümölcs,  amit  a  kígyó  fel  tud  szedni.  Határozza  meg  az  objektumok  kapcsolatát  és felelősségét! Demonstrálja a működést külön modulként fordított tesztprogrammal! A játék állását  nem  kell  grafikusan  megjeleníteni,  elegendő  csak  karakteresen,  a  legegyszerűbb formában! A megoldáshoz ne használjon STL tárolót!  

2. **Pontosított<a name="_page1_x68.00_y464.92"></a> feladatspecifikáció**   

A feladat egy Snake játék elkészítése, amihez az SDL könyvtárat fogom használni, hogy grafikusan is megjeleníthető legyen.
A kígyót a WASD és a nyilak használatával lehet irányítani. A játék teljes egésze egy ablakban fut majd. A játék 2 főbb menüt tartalmaz.
A játék végénél egy külön file-ba kiírjuk a lejátszott körök közül a legjobb pontszámot, címkézve az adott nap dátumával. 

4. **Terv<a name="_page1_x68.00_y580.92"></a>**  
1. **Objektum<a name="_page1_x68.00_y611.92"></a> terv**   

A játék adatstruktúráját tekintve egy változó méretű láncolt lista segítségével fogom elkészíteni. 

Az osztályok: 

- Node: 
- Ez lesz felelős, hogy a kígyónak minden négyzete (eleme) egymás után egy láncolt listában legyen. 
- Snake: 
- Magát a kígyót irányíó és leíró függvények, illetve adattagok itt helyezkednek majd el, ez az osztály lesz felelős a kígyó irányításáért és frissítéséért behatások esetén. Ez az osztály lesz felelős a Snake memóriaterületének felszabadításáért is. 
- Food: 
- A Food osztály egy Node leszármazott, viszont ez csak egy darab Node elem lesz. Ez az egy elem lesz a felelős a teljes Kaja irányításáért. Pontszerzés esetén új kaja kerül a képernyőre, amit egy folyamatos tesztelés fog felügyelni, hogy a kígyó kajára lépett e. 
- Start: 
- Ez az osztály képviseli a teljes Start-menüt, ahol megjelenik az irányítás. 
- Game-End: 
- A Game-End menü lesz a felelős a játék folyamatos futásáért, azaz a Start-menü utáni állapotért. A Game-End menü azért van egybekötve, mert ha a kígyó meghal, abban az esetben is lehessen új játékot kezdeni anélkül is, hogy teljesen újra kelljen indítani az programot. A Game menüben fut majd a játék. Halál esetén áttérünk az End menübe, ahol megjelenik a pontszámunk, valamint az újrakezdéshez, vagy a befejezéshez szükséges gombok. 

![](Aspose.Words.4f87159a-837f-456f-9000-a3a831018364.003.jpeg)

2. **Algoritmusok<a name="_page3_x68.00_y71.92"></a>**       

<a name="_page3_x68.00_y96.92"></a>**4.2.1. Tartományon kívüli elemek lekérése**   

A kígyó mozgásáért felelős algoritmus úgy működik, hogy a kígyónak minden elemét egy láncolt listába tároljuk el. Mozgás esetén a láncolt lista első eleme elé berakunk egy új elemet, attól függően, hogy melyik irányba megy a kígyó, az utolsó elemét pedig kitöröljük, ezáltal nem kell minden egyes mozgásnál a teljes kígyót újra rajzolni, hanem csak kettő elemet kell módosítani/létrehozni. Amennyiben a kígyó elér egy kaját, abban az esetben a feje elé betesszük az új elemet, viszont a végéről nem töröljük a farok elemet, ezáltal a kígyó hossza nő. 

5. **Megjegyzés<a name="_page3_x68.00_y230.92"></a> a tervhez** 

A játék nem tartalmaz tesztelést, csak memóriaszivárgás esetén lép fel egy hibaüzenet, ami tájékoztat esetleges memóriaszivárgásról, amiről egy dump a szabványos kimeneten meg is jelenik. A játék teszteléséhez a játék lejátszása lesz. 

6. **Megvalósítás** 

A  feladat  megvalósításághoz  5  sablonosztály  elkészítését  igényelte.  A  sablonosztályok használják az std::string és az std::fstream és a chrono beépített osztályokat. Az osztályok elkészült interfésze annyiban változott a tervhez képest, hogy logikusabbnak láttam, hogyha  a Snake osztályom nem a Node osztályom leszármazottja, hanem csak Node\*-okból álló duplán láncolt  listát  alkalmaz.  Illetve  a  tesztelések  miatt  néhány  függvénynek  a  „test”  párját implementálni kellet, néhol pedig az alap függvény paramétereit kellett megváltoztatni. 

A teljes projekt 5db (+ a memtrace.cpp) .cpp fájlt 5dbv .hpp fájlt és 2 .h fájlt, és egy .ttf fájlt tartalmaz. Ezek sorrendben: main.cpp, food.cpp, game\_end.cpp, snake.cpp, start.cpp, food.hpp, game\_end.hpp,  node.hpp,  snake.hpp,  start.hpp,  comic.ttf,  gtest\_lite.h,  memtrace.cpp, memtrace.h. 

**6.1. Az elkészített osztálysablonok bemutatása** 

Food: 

Privát adattagok:  

- x – a leendő étel x koordinátája 
- y – a leendő étel y koordinátája 

Public függvények: 

- Food(int, int) – a két koordinátás konstruktor 
- Food(Snake\*, int, int) – a kígyó állapota és a képernyő méreteitől függő konstruktor 
- Food(bool) – teszteléshez szükséges konstruktor 
- int getX() – getter a Food objektum x koordinátájához 
- int getY() – getter a Food objektum y koordinátájához 
- int setX() – setter a Food objektum x koordinátájához 
- int setY() – setter a Food objektum y koordinátájához 
- void newFood(Game\*, Snake\*, Food\*) – létrehoz egy új Food objektumot random 

  koordinátákkal, amit ki is rajzol a pályára 

- void  newFood(Game\*,  Snake\*,  Food\*,  bool)  –  a  teszteléshez  szükséges  newFood függvény 
- bool  foodOnSnake(Snake\*,  Food\*)  –  ez  a  függvény  az  olyan  esetek  elkerüléséért felelős, amikor a Food objektum a kígyóra hoz létre egy új Food objektumot, ezzel eltűntetve a képernyőről 

Game: 

Privát adattagok/függvények: 

- window - az SDL-hez szükséges window pointere 
- renderer - az SDL-hez szükséges megjelenítő ablak pointere 
- w – a képernyő szélessége 
- h – a képernyő magassága 
- sdl\_init – az ablak és a megjelenítő inicializálásáért felelős függvény 

Public függvények: 

- Game(const  char\*,  int,  int)  –  a  Game  osztály  és  az  SDL-t  inicializáló  objektum konstruktora 
- SDL\_Window\* getWindow() – az SDL\_Window\* gettere 
- SDL\_Renderer\* getRenderer() – az SDL\_Renderer\* gettere 
- int getW() – a képernyő szélességének a gettere 
- int getH() -  a képernyő magasságának a gettere 
- void startup(Game\*, Snake\*, Food\*) – a kezdőállapot felrajzolásáért felelős függvény 
- void startup(Game\*, Snake\*, Food\*, bool) – a startup függvény teszteléses változata 
- void game\_Loop(Game\*, bool&, bool&, int&, bool&) – a játék folytonos futásáért és a játék futása alatt a többi osztály függvényeivel a kommunikációért felel 
- void IntoFile(int score) – a játék végén a max.txt- fájlba a rekordot elmentő függvény 
- void clearGame() – a játék végén az SDL\_Window és az SDL\_Renderer elpusztításáért felelős függvény 

Node: 

Privát adattagok/függvények: 

- x – egy Node objektum x koordinátája 
- y – egy Node objektum y koordinátája 
- size – egy Node objektum mérete pixelekben, ami alapján ki lehet rajzolni a képernyőre 
- \*prev – a duplán láncolt listában az előtte lévő elemre mutató pointer 
- \*next – a duplán láncolt listában a következő elemre mutató pointer 

Public függvények: 

- Node() – egy Node objektum default konstruktora 
- Node\* getPrev() – a \*prev adattag gettere 
- Node\* getNext() – a \*next adattag gettere 
- int getX() – az x adattag gettere 
- int getY() – az y adattag gettere 
- int getSize() – a size adattag gettere 
- void setX(int newX) – az x adattag settere 
- void setY(int newY) – az y adattag settere 
- int setSize(int newSize) – a size adattag settere 
- Node\* setPrev(Node\* newPrev) – a \*prev adattag settere 
- Node\* setNext(Node\* newNext) – a \*next adattag settere 
- void clearNode(Node\* node) – egy Node objektum törléséért felelős 

Snake: 

Dir enum – A snake irányának az enum osztálya 

Privát adattagok/függvények: 

- \*head – a Node\*-okból álló duplán láncolt lista első elemére mutató pointer 
- \*tail – a Node\*-okból álló duplán láncolt lista utolsó elemére mutató pointer 
- len – a kígyó Node elemekből álló hossza 
- direction – a fejének az iránya, amerre mozog a képernyőn 

Public függvények: 

- Snake(int, int) – egy Snake objektum alap konstruktora 
- Snake(int, int, bool) – egy Snake objektum teszteléshez szükséges konstruktora 
- Node\*getHead() – a \*head adattag gettere 
- Node\* getTail() – a \*tail adattag gettere 
- Dir getDir() – a direction adattag gettere 
- int getLen() – a len adattag gettere 
- Node\* setHead(Node\* newHead) – a \*head adattag settere 
- Node\* setTail(Node\* newTail) – a \*tail adattag settere 
- int setLen(int newLen) – a len adattag settere 
- Dir setDir(Dir newDir) – a direction adattag settere 
- void snakeUpdate(Game\*, Snake\*, Food\*, bool&, bool) – a kígyó mozgását felügyelő 

  függvény egybeépítve a tesztelésével 

- void clearSnake(Snake\*) – a egy Snake objektum törléséért felelős 

Start: 

Privát adattagok/függvények: 

- \*font – a képernyőn megjelenő szövegek betűtípusa 

Public függvények: 

- void startMenu(SDL\_Renderer\*, bool&, bool&, int, int) – a kezdő menü betöltéséért, kirajzolásáért felelős függvény 
7. **Tesztelés** 

A tesztelés a gtest\_lite.h használatával történik és egy külön ablak megnyílik az elején a teszteléshez. A snake osztály föbb függvényeit lehet tesztelni: 

- snakeUpdate – a kígyó mozgása miatt változó koordináták változása 
- hitFood – a Food objektum eltalálását felügyelő függvény tesztelése 
- hitWall – a Snake objektum a képernyő szélének ütközését figyelő függvényének a tesztelése 
- hitTail – a Snake objektum a saját farkába ütközését figyelő függvény tesztelése 
