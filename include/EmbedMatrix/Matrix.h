#ifndef __EMBED_MATRIX__
#define __EMBED_MATRIX__


#include <stdexcept>
#include <cmath>
#include <cfloat>
#include <typeinfo>
#include <cstring>


namespace Embed {


template<class DataType, int Rows, int Cols>
class Matrix
{
    public:
        // 行列の準備 コンストラクタ
        /**
         * @brief コンストラクタ
         * 
         * @param data : データ配列
         */
        Matrix(DataType * data=NULL):
            _data_num(Rows*Cols), _rows(Rows), _cols(Cols),
            _data_step_size(Cols*sizeof(DataType)),
            _data_size(_data_step_size*Rows)
        {
            _data = (DataType*)malloc(_data_size);

            if(data != nullptr)
            {
                memcpy(_data, data, _data_size);
            }
            else
            {
                memset(_data, 0, _data_size);
            }
        }

        ~Matrix()
        {
            free(_data);
        }

        /**
         * @brief 単位行列に設定
         * 
         */
        void setIndentity()
        {
            for(int i=0; i<Rows; i++)
            {
                for(int j=0; j<Cols; j++)
                {
                    if(i==j)
                    {
                        _data[i*Cols+j] = 1;
                    }
                    else
                    {
                        _data[i*Cols+j] = 0;
                    }
                }                
            }
        }

        /**
         * @brief ゼロ行列に設定
         * 
         */
        void setZeros()
        {
            for(int i=0; i<Rows; i++)
            {
                for(int j=0; j<Cols; j++)
                {
                    _data[i*Cols+j] = 0;
                }                
            }
        }

        /**
         * @brief テキスト表示用
         * 
         */
        operator char*()
        {
            char temp[256];

            sprintf(_print_text_buf, "[\n");

            for(int i=0; i<_rows; i++)
            {
                strcat(_print_text_buf, "[ ");
                for(int j=0; j<_cols; j++)
                {
                    sprintf(temp, "%.2f, ", _data[i*_cols+j]);
                    strcat(_print_text_buf, temp);
                }
                strcat(_print_text_buf, "]\n");
            }
            strcat(_print_text_buf, "]\n");

            return _print_text_buf;
        }

        /**
         * @brief 要素読み込みアクセス
         * 
         */
        DataType* operator[](int i)
        {
            return &_data[_cols * i];
        }

        /**
         * @brief データ配列取得
         * 
         */
        operator DataType*()
        {
            return (DataType*)_data;
        }

        /**
         * @brief 代入
         * 
         */
        Matrix<DataType, Rows, Cols>& operator=(Matrix<DataType, Rows, Cols> m)
        {
            memcpy(_data, m._data, _data_size);
            return *this;
        }

        /**
         * @brief 加算
         * 
         */
        Matrix<DataType, Rows, Cols> operator+(Matrix<DataType, Rows, Cols> m)
        {
            Matrix<DataType, Rows, Cols> tmp;

            for(int i=0; i<Rows; i++)
            {
                for(int j=0; j<Cols; j++)
                {
                    tmp[i][j] = _data[i*Cols+j] + m[i][j];
                }                
            }

            return tmp;
        }

        /**
         * @brief 行列積
         * 
         */
        template<int T>
        Matrix<DataType, Rows, T> operator*(Matrix<DataType, Cols, T> m)
        {
            Matrix<DataType, Rows, T> tmp;
            DataType val = 0;

            for(int i=0; i<Rows; i++)
            {
                for(int j=0; j<T; j++)
                {
                    val = 0;
                    for(int k=0; k<Cols; k++)
                    {
                        val += _data[i*Cols+k] * m[k][j];
                    }
                    tmp[i][j] = val;
                }
            }

            return tmp;
        }

        /**
         * @brief スカラー積
         * 
         */
        Matrix<DataType, Rows, Cols> operator*(float v)
        {
            Matrix<DataType, Rows, Cols> tmp;

            for(int i=0; i<Rows; i++)
            {
                for(int j=0; j<Cols; j++)
                {
                    tmp[i][j] = _data[i*Cols+j] * v;
                }
            }

            return tmp;
        }
        

        /**
         * @brief 転置行列
         * 
         */
        Matrix<DataType, Cols, Rows> T()
        {
            Matrix<DataType, Cols, Rows> tmp;

            for(int i=0; i<Rows; i++)
            {
                for(int j=0; j<Cols; j++)
                {
                    tmp[j][i] = _data[i*Cols+j];
                }
            }

            return tmp;
        }

        /**
         * @brief 余因子
         * 
         */
        Matrix<DataType, Rows-1, Cols-1> cofactor(int tr, int tc)
        {
            int r = rows();
            int c = cols();
            DataType* data = _data;
            DataType tmp_buf[(r-1)*(c-1)];

            cofactor(r, c, data, tr, tc, tmp_buf);

            Matrix<DataType, Rows-1, Cols-1> tmp(tmp_buf);

            return tmp;
        }

        /**
         * @brief 行列式
         *          
         */
        DataType determinant()
        {
            DataType* data = _data;
            int r = rows();
            int c = cols();

            if( r != c )
            {
                throw std::logic_error("determinant only square matrix");
            }

            return determinant(r, c, data);
        }

        /**
         * @brief 逆行列(型確認)
         * 
         * @return Matrix<float, Rows, Cols> 
         */
        Matrix<float, Rows, Cols> invert()
        {
            DataType det = determinant();            

            if(fabs(det) < FLT_EPSILON)
            {
                throw std::logic_error("determinant 0 value");
            }

            return invertBase();
        }

        size_t rows(){ return _rows; }
        size_t cols(){ return _cols; }

    private:
        const size_t    _data_num;
        const size_t    _rows;
        const size_t    _cols;

        const size_t    _data_step_size;
        const size_t    _data_size;

        DataType* _data;


        char _print_text_buf[512];

        /**
         * @brief 行列式
         * 
         */
        DataType determinant(int r, int c, DataType* data)
        {
            if( r == 1 ){
                return data[0];
            }

            DataType val = 0;
            DataType a = 0;
            DataType b = 0;
            DataType tmp[(r-1)*(c-1)];

            for(int i=0; i<r; i++)
            {
                a = data[i*c+0];

                cofactor(r, c, data, i, 0, tmp);
                b = determinant(r-1, c-1, tmp);

                if(i%2==0)
                {
                    val += a * b;
                }
                else
                {
                    val -= a * b;
                }
            }

            return val;
        }

        /**
         * @brief 余因子展開
         * 
         */
        void cofactor(int r, int c, DataType* src, int tr, int tc, DataType* dst)
        {
            int dr = r - 1;
            int dc = c - 1;

            for(int i=0; i<r; i++)
            {
                for(int j=0; j<c; j++)
                {
                    if(i < tr)
                    {
                        if(j < tc)
                        {
                            dst[i*dc+j] = src[i*c+j];
                        }
                        else if(j > tc)
                        {
                            dst[i*dc+j-1] = src[i*c+j];
                        }
                    }
                    else if(i > tr)
                    {
                        if(j < tc)
                        {
                            dst[(i-1)*dc+j] = src[i*c+j];
                        }
                        else if(j > tc)
                        {
                            dst[(i-1)*dc+j-1] = src[i*c+j];
                        }
                    }
                }
            }
        }

        /**
         * @brief 逆行列
         * 
         * @return Matrix<DataType, Rows, Cols> 
         */
        Matrix<DataType, Rows, Cols> invertBase()
        {
            int r = rows();
            int c = cols();
            DataType det = determinant();
            Matrix<DataType, Rows, Cols> ans;
            Matrix<DataType, Rows-1, Cols-1> tmp;
            DataType det_a;

            if( r != c )
            {
                throw std::logic_error("invert only square matrix");
            }

            for(int i=0; i<r; i++)
            {
                for(int j=0; j<c; j++)
                {
                    tmp = cofactor(i, j);
                    det_a = tmp.determinant();

                    if((i+j)%2==0)
                    {
                        ans[j][i] = det_a / det;
                    }
                    else
                    {
                        ans[j][i] = - det_a / det;
                    }
                }
            }

            return ans;
        }
};


};

#endif