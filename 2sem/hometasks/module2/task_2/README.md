# Задача B
### Условие:
Необходимо написать торгового советника для поиска арбитража.
Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют:

GBP/USD: 0.67

RUB/GBP: 78.66

USD/RUB: 0.02

Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4%.
### Формат ввода
Первая строка содержит число N – количество возможных валют (определяет размер таблицы котировок). 
Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены (подразумевается, что курс валюты к себе же 1.0). 
В элементе таблицы (i, j) содержится обменный курс i->j. 
Если обмен в данном направлении не производится, то -1.
### Формат вывода
Выведите YES, если арбитраж есть, и NO, иначе.

### Формирование графа
Пусть даны n валют, ![equation](https://latex.codecogs.com/gif.latex?\omega(i,&space;j)) - функция курса i-ой валюты к j-ой.

Если для некоторой валюты существует последовательность обменов, при которой конечная денежная сумма в той же валюте больше изначальной, то верно:

![equation](https://latex.codecogs.com/gif.latex?1\times\omega(1,&space;2)\times\omega(2,&space;3)\times\dotsc\times\omega(k-1,&space;k)\times\omega(k,&space;1)&space;>&space;1)

![equation](https://latex.codecogs.com/gif.latex?\frac{1}{\omega(1,&space;2)}\times\frac{1}{\omega(2,&space;3)}\times\dotsc\times\frac{1}{\omega(k,&space;1)}&space;<&space;1)

![equation](https://latex.codecogs.com/gif.latex?ln&space;\Bigg(&space;\frac{1}{\omega(1,&space;2)}\times&space;\frac{1}{\omega(2,&space;3)}&space;\times&space;\dotsc&space;\times&space;\frac{1}{\omega(k,&space;1)}&space;\Bigg)&space;<&space;0)

![equation](https://latex.codecogs.com/gif.latex?ln&space;\frac{1}{\omega(1,&space;2)}&space;&plus;&space;ln&space;\frac{1}{\omega(2,&space;3)}&space;&plus;&space;\dotsc&space;&plus;&space;ln&space;\frac{1}{\omega(k,&space;1)}&space;<&space;0)

![equation](https://latex.codecogs.com/gif.latex?-ln&space;\big(&space;\omega(1,&space;2)&space;\big)&space;-&space;ln&space;\big(&space;\omega(1,&space;2)&space;\big)&space;-&space;\dotsc&space;-&space;ln&space;\big(&space;\omega(k,&space;1)&space;\big)&space;<&space;0)

Задача свелась к нахождению цикла отрицательного веса в графе с вершинами-валютами и рёбрами между конвертируемыми валютами с весами ![equation](https://latex.codecogs.com/gif.latex?-ln&space;\big(&space;\omega(i,&space;j)&space;\big)): если он есть, то возможны валютные махинации.

Проверка на такой цикл осуществляется алгоритмом Беллмана-Форда за ![equation](https://latex.codecogs.com/gif.latex?T(|V|,&space;|E|)&space;=&space;\mathcal{O}(|V||E|)).
