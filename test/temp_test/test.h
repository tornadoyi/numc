class CwiseBinaryOp;

class ArrayBase
{
public:
    ArrayBase operator+(ArrayBase& a)
    {
        return CwiseBinaryOp(*this, a);
    }
};


class Array : public ArrayBase
{

};

class CwiseBinaryOp : public ArrayBase
{
public:
    CwiseBinaryOp(ArrayBase& a, ArrayBase& b)
    {
        src = a;
        dst = b;
    }

    ArrayBase src;
    ArrayBase dst;
};