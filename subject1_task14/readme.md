## Задача 14

| параметр:               | значение: |
| ----------------------- | --------- |
| Имя входного файла:     | tst.in    |
| Имя выходного файла:    | tst.out   |
| Ограничение по времени: | 1 с       |
| Ограничение по памяти:  | нет       |

### Условие

Необходимо найти пути минимальной длины между корнем и листьями и удалить в
порядке возрастания ключей средние по значению вершины этих путей (левым
удалением), если они существуют.

### Замечание

Если некоторая вершина является средней по значению для нескольких путей
минимальной длины, то удаляется она только один раз.

### Формат входного файла

Входной файл содержит последовательность чисел — ключи вершин в порядке
добавления в дерево.

### Формат выходного файла

Выходной файл должен содержать последовательность ключей вершин, полученную
прямым левым обходом итогового дерева.
