# 4 laboratonis darbas - Trumpiausio kelionės maršruto ir ilgio paieška

## Bendradarbiavimas
Užduotis atlikta kartu su raki1805, kuris man padėjo sukurti grafą.

## Varianto sąlyga
Duotas kelių sąrašas: miestas, miestas, atstumas. Rasti trumpiausią kelionės iš vieno duoto miesto į kitą duotą miestą maršrutą ir jo ilgį. Numatyti atvejį, kad toks maršrutas neegzistuoja. (grafo realizacija paremta kaimynystės matrica)

## Algoritmas
Greičiausio kelio paieškai naudojamas Dijkstros algoritmas.

## Įvesties failo formatas

Pirmoje eilutėje yra pradinis ir galutinis taškai, o tolesniuose eilutėse
įvedami du miestai ir atstumas tarp jų.

## Kompiliavimas ir paleidimas

Automatinis visų testų generavimas, kompiliavimas ir vykdymas:
```
Go.cmd
```
    