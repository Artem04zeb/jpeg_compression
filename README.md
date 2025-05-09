# Сжатие изображений в формат JPEG
Implementation core algorithms for jpeg compression using OpenCV library

---
# Алгоритм сжатия
1. Считывание изображения <br>
**Прим**: обычно изображение читается в формате BGR (OpenCV по умолчанию) <br>
Но для дальнейшего шага переводить RGB → BGR не стоит. Проще сразу BGR → YCbCr <br>
1. Преобразование в YCbCr <br>
* Функция convertToYCbCr
1. Деление каждого канала на блоки 8×8 <br>
* Функция splitIntoBlocks
* Дополнительно, если ширина/высота не кратны 8, функция padToBlockSize
1. Центрирование значений (вычитание 128) <br>
* Функция centerBlocks
1. Применение 2D-DCT к каждому 8×8 блоку <br>
* Функция applyDCTToBlocks
1. Квантование DCT-коэффициентов <br>
* Функция quantizeBlocks
1. Зигзагообразное сканирование <br>
* Функция zigzagScan
* Обратная для декодирования zigzagUnscan
1. Run-Length Encoding (RLE) <br>
* Функция runLengthEncode
* Для декомпрессии, функция runLengthDecode
1. Сборка результата <br>
* saveCompressed() или сериализация в CompressedImage
---
# Алгоритм декомпрессии
Идёт в обратном порядке:
Хаффман → RLE → Zigzag → Деквантование → IDCT → +128 → объединение блоков → Upsample Cb/Cr → YCbCr → RGB.