#include "icom.h"
#include "icom_p.h"
using namespace NetDriver;

//private class
IComPrivate::IComPrivate()
{

}
IComPrivate::~IComPrivate()
{

}

ICom::ICom():d_ptr(new IComPrivate())
{
  d_ptr->q_ptr=this;

}
ICom::~ICom()
{
  delete d_ptr;
}

ICom::ICom(IComPrivate &d):d_ptr(&d)
{
  d_ptr->q_ptr=this;
}


