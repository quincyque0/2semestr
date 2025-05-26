<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Мои достижения - 2 семестр</title>
    <style>
        :root {
            --primary: #2c3e50;
            --secondary: #3498db;
            --accent: #e74c3c;
            --light: #ecf0f1;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0;
            background-color: var(--light);
            color: var(--primary);
        }
        
        header {
            background: linear-gradient(135deg, var(--primary), var(--secondary));
            color: white;
            padding: 2rem 0;
            text-align: center;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 0 20px;
        }
        
        h1 {
            margin: 0;
            font-size: 2.5rem;
        }
        
        .subtitle {
            font-style: italic;
            opacity: 0.9;
        }
        
        .semester-info {
            display: flex;
            justify-content: space-around;
            flex-wrap: wrap;
            margin: 2rem 0;
        }
        
        .card {
            background: white;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            padding: 1.5rem;
            margin: 1rem;
            width: 300px;
            transition: transform 0.3s ease;
        }
        
        .card:hover {
            transform: translateY(-5px);
        }
        
        .card h2 {
            color: var(--secondary);
            border-bottom: 2px solid var(--secondary);
            padding-bottom: 0.5rem;
        }
        
        .progress-bar {
            height: 10px;
            background-color: #e0e0e0;
            border-radius: 5px;
            margin: 1rem 0;
            overflow: hidden;
        }
        
        .progress {
            height: 100%;
            background-color: var(--accent);
            width: 0;
            transition: width 1s ease;
        }
        
        footer {
            text-align: center;
            padding: 2rem 0;
            background-color: var(--primary);
            color: white;
        }
        
        @media (max-width: 768px) {
            .semester-info {
                flex-direction: column;
                align-items: center;
            }
        }
    </style>
</head>
<body>
    <header>
        <div class="container">
            <h1>Мой учебный прогресс</h1>
            <p class="subtitle">2 семестр - путь к знаниям</p>
        </div>
    </header>
    
    <div class="container">
        <section class="semester-info">
            <div class="card">
                <h2>Программирование на C</h2>
                <p>Изучение основ языка C, алгоритмов и структур данных.</p>
                <div class="progress-bar">
                    <div class="progress" style="width: 75%"></div>
                </div>
                <p>75% выполнено</p>
            </div>
            
            <div class="card">
                <h2>Дискретная математика</h2>
                <p>Логика, теория графов, комбинаторика.</p>
                <div class="progress-bar">
                    <div class="progress" style="width: 60%"></div>
                </div>
                <p>60% выполнено</p>
            </div>
            
            <div class="card">
                <h2>Алгоритмы и структуры данных</h2>
                <p>Сортировки, деревья, хеш-таблицы.</p>
                <div class="progress-bar">
                    <div class="progress" style="width: 50%"></div>
                </div>
                <p>50% выполнено</p>
            </div>
        </section>
        
        <section class="card" style="width: 100%; max-width: 800px; margin: 2rem auto;">
            <h2>Мои достижения</h2>
            <ul>
                <li>Написал первую программу на C, которая работает!</li>
                <li>Решил 20+ задач по дискретной математике</li>
                <li>Освоил работу с указателями (почти)</li>
                <li>Сдал 3 лабораторные работы</li>
            </ul>
        </section>
    </div>
    
    <footer>
        <div class="container">
            <p>© 2023 Мой учебный прогресс | 2 семестр</p>
        </div>
    </footer>
    
    <script>
        // Анимация прогресс-баров при загрузке страницы
        document.addEventListener('DOMContentLoaded', function() {
            const progressBars = document.querySelectorAll('.progress');
            progressBars.forEach(bar => {
                const width = bar.style.width;
                bar.style.width = '0';
                setTimeout(() => {
                    bar.style.width = width;
                }, 100);
            });
        });
    </script>
</body>
</html>
