/**

 Harsha's Chaos Index

Recently, Sunil handed some list of numbers to harshendra. The Numbers are written in some random order.
Harshendra loves to have everything organized. So he decided to sort the list of numbers in ascending order. Before sorting, Harshendra wants to find 'Chaos Index' of the list so that he can know how far array is from being sorted.
Chaos index = Number of pairs which satisfies condition : ( i < j and ai > aj)
i, j = position of numbers in list
ai, aj = number
Can you help harshendra finding chaos index ?
Input

    Line 1 : N
    Number of elements in list
    Line 2 : a1 a2 .. an
    N space seperated integers

Output

    Chaos Index

Constraints

    1 <= N <= 105
    -106 <= ai <= 106

Example
Input1
5
2 4 1 3 5

Output1
3

Input2
5
1 2 3 4 5
Output2
0

**/