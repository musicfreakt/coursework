# Курсовая работа по программированию

---

## Содержание:
- [Немного информации о программе](#description)
- [Структрура репозитория](#structure)
- [Компиляция](#compile)

---

## <a name="description"></a> Немного информации о программе

Программа предназначена для работы с электронной картотекой музыкальных композиций

Поля информационной структуры:

- char* artist - Имя исполнителя
- сhar* title - Название
- char* album - Альбом, на котором выпущена композиция
- int number - Номер композиции в альбоме
- int year - Год выхода композиции
- int genre - Жанр музыки

Картотека хранится в памяти компьютера в виде двусвязного линейного списка.

Для более подробной информации смотрите отчет в папке *report*.

Ссылка на презентацию: <a href = "https://docs.google.com/presentation/d/1GUBhEG9AbZejZgfR08s8CG6jVtFfDiClSagsC0dvtyg/edit?usp=sharing">ТЫК</a>

Ссылка на критику: <a href = "https://docs.google.com/document/d/1GXmWf7tfhLAJDq-Fc5btxh4ubcm_y4a3yM6V3M59BZk/edit">ТЫК</a>

## <a name="structure"></a> Структура репозитория

Репозиторий содержит две папки:

1) **report** - Папка, в которой содержатся файлы для отчета и сам отчет
2) **src** - Папка, в которой содержится исходный код курсовой работы


Папка *src/* содержит следующие файлы:

- **constants.h** - Заголовочный файл с константами программы
- **help_func.h** - Заголовочный файл для вспомогательных функций
- **help_func.c** - Реализация вспомогательных функций
- **dlist.h** - Заголовочный файл библиотеки для работы с двусвязным линейным списком
- **dlist.c** - Реализация функций для работы с двусвязным линейным списком
- ***data.csv*** - Небольшой файл с данными для теста программы

## <a name="compile"></a> Компиляция
(Только для *gcc* (linux) и *mingw* (windows))

В главной директории репозитория есть два исполняемых файла:

- **compile.bat**
- **compile.sh**

Данные файлы компилируют программу для OC Windows и GNU/Linux соответственно.
В итоге получается исполняемый файл с именем *main.exe* или *main.o*, 
который вы можете запустить. (Простите, но готового экзешничка нет))

Также в репозитории есть файлы **test.sh** и **leaks.sh**, который были созданы для тестирования программы на ошибки и утечки памяти.
