#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

//-------------------------------------------------------------------------------------------------
class Rectangle 
{
public:
  Rectangle(int width, int height);

  int GetArea() const;
  int GetPerimeter() const;
  int GetWidth() const;
  int GetHeight() const;
private:
  int width_; 
  int height_;
};
//-------------------------------------------------------------------------------------------------
#endif //_RECTANGLE_H_