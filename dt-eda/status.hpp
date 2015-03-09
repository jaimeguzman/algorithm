/**
   \file status.hpp
   \brief Header file for status.cpp.
*/

//! Text-mode status bar used in verbose mode in learning algorithms.

class Status {

public:

  Status(int n=55);
  void update(double p);
  ~Status();
  void reset();

private:

  int n;
  int last;
}; 
