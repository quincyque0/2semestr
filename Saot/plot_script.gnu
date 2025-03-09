# Сохраняем данные в таблицу
set table "table_data.txt"
plot 'data1.txt' using 1:2 with lines title 'SelectSort', \
     'data1.txt' using 1:3 with lines title 'BubbleSort', \
     'data1.txt' using 1:4 with lines title 'ShakerSort', \
     'data1.txt' using 1:5 with lines title 'InsertSort'
unset table

# Строим график
set title 'Сравнение трудоемкости сортировок'
set xlabel 'Размер массива (N)'
set ylabel 'Трудоемкость (T)'
set grid
plot 'data1.txt' using 1:2 with lines title 'SelectSort', \
     'data1.txt' using 1:3 with lines title 'BubbleSort', \
     'data1.txt' using 1:4 with lines title 'ShakerSort', \
     'data1.txt' using 1:5 with lines title 'InsertSort'

# Сохраняем график в файл
set terminal png size 2400,1600
set output 'sort_graph.png'
replot