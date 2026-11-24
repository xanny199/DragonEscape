# Dragon Escape

Dragon Escape je konzolová dobrodružná hra napísaná v jazyku **C** pre **Windows**.
Hráč zbiera suroviny v dračom brlohu, získava skúsenosti, nakupuje vybavenie a pripravuje sa na záverečný súboj s drakom.

## Pravidlá hry

- Hra sa začína v obchode, ktorý je bezpečnou zónou.
- V dračom brlohu môže hráč zbierať drevo, kameň, železo a kryštály.
- Za zbieranie surovín získava skúsenosti (XP) a postupuje na vyššie úrovne.
- V obchode môže predávať suroviny, kupovať predmety, používať elixíry a vylepšovať postavu.
- Po **60 sekundách** v brlohu sa objaví drak a začne sa ťahový súboj.
- Po výhre alebo prehre sa hra vráti do hlavného menu.

## Ovládanie

| Kláves | Akcia |
|---|---|
| `W`, `A`, `S`, `D` | Pohyb hráča |
| `E` | Obchodník (v jeho blízkosti) |
| `I` | Vybavenie (v obchode) |
| `P` | Elixíry (v obchode) |
| `Q` | Ukončenie aktuálnej hry |

V ponukách sa používajú číselné voľby zobrazené na obrazovke.

## Spustenie

Projekt je určený pre **Windows** a používa knižnice `conio.h` a `windows.h`.
Na kompiláciu je možné použiť **GCC z MSYS2 UCRT64**.

V termináli MSYS2 UCRT64, v priečinku projektu, spustite:

```bash
gcc -std=c11 -Wall -Wextra main.c game.c player.c map.c resource.c inventory.c shop.c dragon.c combat.c timer.c -o DragonEscape.exe
./DragonEscape.exe
```

## Štruktúra projektu

- `main.c`, `game.c` – hlavné menu a herný cyklus
- `player.c`, `map.c`, `resource.c` – hráč, mapa a suroviny
- `inventory.c`, `shop.c` – inventár, vybavenie, elixíry a obchod
- `timer.c`, `dragon.c`, `combat.c` – časovač, drak a súboj

Súbory `.h` obsahujú deklarácie typov a funkcií príslušných modulov.