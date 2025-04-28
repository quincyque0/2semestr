import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv('results.csv', header=None, names=['Size', 'Threads', 'Time'])
pivoted = df.pivot(index='Size', columns='Threads', values='Time')

plt.figure(figsize=(12, 8))
for column in pivoted.columns:
    plt.plot(pivoted.index, pivoted[column], label=f'{column} Потоки', marker='o')

plt.xlabel('Размер')
plt.ylabel('Время (ms)')
plt.title('Тестирование потоков')
plt.legend()
plt.grid(True)
plt.savefig('performance_plot.png')
plt.show()
