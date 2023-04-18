«Нельзя отворачиваться от семьи. Даже если она отвернулась от тебя» (c) Форсаж 6. Все дороги принадлежат им!

Вы решили собрать всю семью вместе, чтобы узнать, как у них настрой. Пока еще никто не приехал (семья же отвернулась), но вот-вот они будут тут. Вы хотите понимать, каково суммарное настроение у семьи и ее подсемей. Для этого вы хотите уметь следующие вещи:

    add(i) — обработать приезд нового члена семьи с настроем i (если он там уже есть, то состав приехавших не изменился, и было введено ошибочное значение);
    sum(l, r) — вывести суммарное настроение всех членов с настроем x, которые удовлетворяют неравенству l ≤ x ≤ r.

Формат ввода

Изначально никто не прибыл еще. Первая строка входного файла содержит n — количество запросов (1 ≤ n ≤ 3*10^5). Следующие n строк содержат операции. Каждая операция имеет вид либо «+ i», либо «? l r». Операция «? l r» задает запрос sum(l, r).

Если операция «+ i» идет во входном файле в начале или после другой операции «+», то она задает операцию add(i). Если же она идет после запроса «?», и результат этого запроса был y, то выполняется операция .

Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 10^9.
Формат вывода

Для каждого запроса выведите одно число — ответ на запрос.
Пример
Ввод:
6
+ 1
+ 3
+ 3
? 2 4
+ 1
? 2 4

Вывод:
3
7