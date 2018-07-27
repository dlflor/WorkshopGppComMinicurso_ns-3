

#include "ns3/object.h"
#include "ns3/uinteger.h"
#include "ns3/traced-value.h"
#include "ns3/traced-callback.h"
#include "ns3/trace-source-accessor.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace ns3;


class MyObject : public Object
{
public:
  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void)
  {
    static TypeId tid = TypeId ("MyObject")
      .SetParent<Object> ()
      .SetGroupName ("Tutorial")
      .AddConstructor<MyObject> ()
      .AddTraceSource ("",
                       "",
                       MakeTraceSourceAccessor (&,
                       "");


    return tid;
	}

  MyObject () {}


};


int
main (int argc, char *argv[])
{   int a;
    int i;
    int j=0;
    int b=0;

  Ptr<MyObject> myObject = CreateObject<MyObject> ();

  // Conectar as sources com as sinks

  myObject->TraceConnectWithoutContext ("", MakeCallback (&));




}
