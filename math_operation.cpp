#include "math_operation.h"

math_operation::math_operation()
{

}

double uniform_rand(double lowerBndr, double upperBndr)
{
  return lowerBndr + ((double) std::rand() / (RAND_MAX + 1.0)) * (upperBndr - lowerBndr);
}
double gauss_rand(double mean, double sigma)
{
  double x, y, r2;
  do {
    x = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
    y = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
    r2 = x * x + y * y;
  } while (r2 > 1.0 || r2 == 0.0);
  return mean + sigma * y * std::sqrt(-2.0 * log(r2) / r2);
}

double Distance(QVector<double> &x, QVector<double> &y)
{
    int i=0;
    int m=x.size();
    double ans=0;
    for(i=0;i<m;i++)
    {
        ans+=(x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(ans);
}

Point::Point(double x1, double y1, double z1)
{
    x=x1;
    y=y1;
    z=z1;
}

Point Point::operator*(double &num)
{
    Point ans(0,0,0);
    ans.x=this->x*num;
    ans.y=num*(this->y);
    ans.z=num*z;
    return ans;
}

double Distance(Point &x, Point &y)
{
    double ans=0;
    ans+=(x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y)+(x.z-y.z)*(x.z-y.z);
    return sqrt(ans);
}

QVector<Complex> FFT(QVector<double> &x)
{
    //快速傅里叶变换，采用迭代的方式而非递归

    int m=x.size();
    QVector<int> r(m+1,0);

    int n=1;
    for(n=1;n<=m;n<<=1)
    {

    }

    QVector<Complex> A(n);
    int i=0;
    for(i=0;i<m;i++)
    {
        A[i].real=x[i];

        A[i].image=0;
    }
    FFT(A);

/*    for(i=0;i<m;i++)
    {
        if(i<r[i])
            qSwap(x[i],x[r[i]]);

    }

    for(int mid=1;mid<m;mid<<=1)
    {
        Complex Wn(cos(pi/mid),sin(pi/mid));
        for(int R=mid<<1,j=0;j<m;j+=R)
        {
            Complex w(1,0);
            for(int k=0;k<mid;k++,w=w*Wn)
            {
                Complex x1=A[j+k],y1=w*A[j+mid+k];
                A[j+k]=x1+y1;
                A[j+mid+k]=x1-y1;
            }
        }
    }
*/
    qDebug()<<"FFT";
    return A;
}

Complex Complex::operator+(Complex &x)
{
    Complex ans=*this;
    ans.real+=x.real;
    ans.image+=x.image;
    return ans;
}

Complex Complex::operator-(Complex &x)
{
    Complex ans=*this;
    ans.real-=x.real;
    ans.image-=x.image;
    return ans;
}

Complex Complex::operator*(Complex &x)
{
    Complex ans;
    ans.real=real*x.real-image*x.image;
    ans.image=real*x.image+image*x.real;
    return ans;
}

Complex::Complex(double r, double i)
{
    real=r;
    image=i;
}

double Complex::amp()
{
    return sqrt(real*real+image*image);
}

void FFT(QVector<Complex> &A)
{
    int m=A.size();
    if(m<=1)
        return ;
    int i=0;
    QVector<Complex> even(m/2);
    QVector<Complex> odd(m/2);
    for(i=0;i<m-1;i+=2)
    {
        odd[i>>1]=A[i+1];
        even[i>>1]=A[i];
    }
    FFT(odd);
    FFT(even);
    for(int k=0;k<m/2;k++)
    {
        Complex t=Polar(1,-2*pi*k/m)*odd[k];
        A[k]=even[k]+t;
        A[k+m/2]=even[k]-t;
    }
}

Complex Polar(double amp, double phi)
{
    Complex ans;
    ans.real=amp*cos(phi);
    ans.image=amp*sin(phi);
    return ans;
}

vec3::vec3(double x1, double y1, double z1)
{
    x=x1;
    y=y1;
    z=z1;
}

vec3 vec3::operator*(double &num)
{
    vec3 ans;
    ans.x=x*num;
    ans.y=y*num;
    ans.z=z*num;
    return ans;
}

double vec3::operator*(vec3 &v2)
{
    return x*v2.x+y*v2.y+z*v2.z;

}

vec3 vec3::operator-(vec3 &v2)
{
    vec3 ans;
    ans.x=x-v2.x;
    ans.y=y-v2.y;
    ans.z=z-v2.z;
    return ans;
}

vec3 vec3::operator+(vec3 &v2)
{
    vec3 ans;
    ans.x=x+v2.x;
    ans.y=y+v2.y;
    ans.z=z+v2.z;
    return ans;
}

vec3 vec3::norm()
{
    vec3 ans;
    double leng=this->len();
    if(leng==0)
        return ans;
    ans.x=x/leng;
    ans.y=y/leng;
    ans.z=z/leng;
    return ans;
}

double vec3::len()
{
    return x*x+y*y+z*z;
}
