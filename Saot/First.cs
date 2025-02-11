using System;

public class Program
{
    // Заполняет массив последовательными числами, начиная с begin
    static int[] FillLine(int begin, int size, int[] array)
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = begin + i;
        }
        return array;
    }

    // Заполняет массив убывающими числами, начиная с begin
    static int[] FillDie(int begin, int size, int[] array)
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = begin - i;
        }
        return array;
    }

    // Заполняет массив случайными числами
    static int[] FillRand(int size, int[] array)
    {
        Random rand = new Random(); // Создаем экземпляр Random для генерации чисел
        for (int i = 0; i < size; i++)
        {
            array[i] = rand.Next(); // Генерируем случайное положительное число
        }
        return array;
    }

    // Считает количество серий в массиве, где каждый следующий элемент меньше предыдущего
    static int RunNumber(int size, int[] array)
    {
        int maxSeries = 1;
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i + 1] < array[i])
            {
                maxSeries++;
            }
        }
        return maxSeries;
    }

    // Вычисляет сумму элементов массива
    static int CheckSum(int size, int[] array)
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += array[i];
        }
        return sum;
    }

    // Выводит первые 10 элементов массива на консоль
    static void Printer(int[] array)
    {
        for (int i = 0; i < Math.Min(10, array.Length); i++) // Используем Math.Min, чтобы избежать выхода за пределы массива
        {
            Console.Write(array[i] + " ");
        }
        Console.WriteLine(); // Переходим на новую строку после вывода
    }

    public static void Main(string[] args)
    {
        int n = 10;
        int sum = 0;
        int[] A = new int[n]; // Создаем массив фиксированного размера

        Console.WriteLine("FillRand:");
        FillRand(n, A);
        Printer(A);
        sum = CheckSum(n, A);
        Console.WriteLine($"Summ = {sum}");
        Console.WriteLine($"Ser = {RunNumber(n, A)}");
        Console.WriteLine();

        Console.WriteLine("FillDie:");
        FillDie(10, n, A);
        Printer(A);
        sum = CheckSum(n, A);
        Console.WriteLine($"Summ = {sum}");
        Console.WriteLine($"Ser = {RunNumber(n, A)}");
        Console.WriteLine();

        Console.WriteLine("FillLine:");
        FillLine(1, n, A);
        Printer(A);
        sum = CheckSum(n, A);
        Console.WriteLine($"Summ = {sum}");
        Console.WriteLine($"Ser = {RunNumber(n, A)}");
        Console.WriteLine();
        

    }
}