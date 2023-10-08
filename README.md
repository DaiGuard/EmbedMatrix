# EmbedMatrix

Arduinoフレームワークで使用できる行列計算ライブラリ

---

## Function

- 行列宣言

```c++
/**
 * @brief 行列を確保
 * 
 * @param DataType: データ型
 * @param Rows: 縦数 
 * @param Cols: 横数
 * @param data: 初期要素データ
 */

// float型 3x3行列
Matrix<float, 3, 3> a;
Serial.println(a);
// [[0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f]]

// int型 2x3行列
int data[6] = [
    1, 2, 3,
    4, 5, 6
];
Matrix<int, 2, 3> b(data);
Serial.println(b);
// [[1, 2, 3],
//  [4, 5, 6]]
```

- 初期化：単位行列

```c++
Matrix<float, 3, 3> a;
a.setIdentity();
Serial.println(a);
// [[1.0f, 0.0f, 0.0f],
//  [0.0f, 1.0f, 0.0f],
//  [0.0f, 0.0f, 1.0f]]
```

- 初期化：ゼロ行列

```c++
Matrix<float, 3, 3> a;
a.setZeros();
Serial.println(a);
// [[0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f]]
```

- 要素代入

```c++
Matrix<float, 3, 3> a;
a.setZeros();
Serial.println(a);
// [[0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f]]

a[1][2] = 10.0f;
Serial.println(a);
// [[0.0f, 0.0f,  0.0f],
//  [0.0f, 0.0f, 10.0f],
//  [0.0f, 0.0f,  0.0f]]
```

- 要素取得

```c++
// int型 2x3行列
int data[6] = [
    1, 2, 3,
    4, 5, 6
];
Matrix<int, 2, 3> b(data);
Serial.println(b);

// [[1, 2, 3],
//  [4, 5, 6]]
int v = b[0][1];
Serial.println(v);
// 2
```

- 代入

```c++
float data_a[9] = [
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
]
Matrix<float, 3, 3> a(data_a);
Serial.println(a);
// [[1.0f, 2.0f, 3.0f],
//  [4.0f, 5.0f, 6.0f],
//  [7.0f, 8.0f, 9.0f]]
Matrix<float, 3, 3> b;
Serial.println(b);
// [[0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f],
//  [0.0f, 0.0f, 0.0f]]

b = a;
Serial.println(b);
// [[1.0f, 2.0f, 3.0f],
//  [4.0f, 5.0f, 6.0f],
//  [7.0f, 8.0f, 9.0f]]
```

- 行列加算

```c++
float data_a[9] = [
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
]
Matrix<float, 3, 3> a(data_a);
Serial.println(a);
// [[1.0f, 2.0f, 3.0f],
//  [4.0f, 5.0f, 6.0f],
//  [7.0f, 8.0f, 9.0f]]

float data_b[9] = [
    1.0f, 4.0f, 7.0f,
    2.0f, 5.0f, 8.0f,
    3.0f, 6.0f, 9.0f
]
Matrix<float, 3, 3> b(data_b);
Serial.println(b);
// [[1.0f, 4.0f, 7.0f],
//  [2.0f, 5.0f, 8.0f],
//  [3.0f, 6.0f, 9.0f]]

Matrix<float, 3, 3> c;
c = a + b;
Serial.println(c);
// [[ 2.0f,  6.0f, 10.0f],
//  [ 6.0f, 10.0f, 14.0f],
//  [10.0f, 14.0f, 18.0f]]

```

- 行列積

```c++
float data_a[9] = [
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
]
Matrix<float, 3, 3> a(data_a);
Serial.println(a);
// [[1.0f, 2.0f, 3.0f],
//  [4.0f, 5.0f, 6.0f],
//  [7.0f, 8.0f, 9.0f]]

float data_b[9] = [
    1.0f, 4.0f, 7.0f,
    2.0f, 5.0f, 8.0f,
    3.0f, 6.0f, 9.0f
]
Matrix<float, 3, 3> b(data_b);
Serial.println(b);
// [[1.0f, 4.0f, 7.0f],
//  [2.0f, 5.0f, 8.0f],
//  [3.0f, 6.0f, 9.0f]]

Matrix<float, 3, 3> c;
c = a * b;
Serial.println(c);
// [[14.0f,  32.0f,  50.0f],
//  [32.0f,  77.0f, 122.0f],
//  [50.0f, 122.0f, 194.0f]]
```

- 転置行列

```c++
float data_a[9] = [
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
]
Matrix<float, 3, 3> a(data_a);
Serial.println(a);
// [[1.0f, 2.0f, 3.0f],
//  [4.0f, 5.0f, 6.0f],
//  [7.0f, 8.0f, 9.0f]]

Matrix<float, 3, 3> t;
t = a.T()
Serial.println(t);
// [[1.0f, 4.0f, 7.0f],
//  [2.0f, 5.0f, 8.0f],
//  [3.0f, 6.0f, 9.0f]]
```

- 行列式

```c++
float data_a[9] = [
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
]
Matrix<float, 3, 3> a(data_a);
Serial.println(a);
// [[1.0f, 2.0f, 3.0f],
//  [4.0f, 5.0f, 6.0f],
//  [7.0f, 8.0f, 9.0f]]

float det = a.determinant();
Serial.println(det)
// 0.0
```

- 逆行列

```c++
float data_a[9] = [
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
]
Matrix<float, 3, 3> a(data_a);
Serial.println(a);
// [[ 1.0f, 2.0f,  3.0f],
//  [-2.0f, 4.0f, -2.0f],
//  [ 3.0f, 2.0f,  1.0f]]

Matrix<float, 3, 3> inv;
inv = a.invert();
Serial.println(inv);
// [[-0.166f,-0.083f, 0.333f],
//  [ 0.083f, 0.166f, 0.083f],
//  [ 0.333f,-0.083f,-0.166f]]
```

## TODO

- [x] 逆行列機能の実装
- [x] スカラー積機能の実装
- [ ] 例題プログラムの実装
- [ ] 単体テストの実装