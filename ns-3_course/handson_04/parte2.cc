
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
      .AddTraceSource ("MyInteger",
                       "An integer value to trace.2",
                       MakeTraceSourceAccessor (&MyObject::varint),
                       "ns3::TracedValueCallback::Int32");


    return tid;
	}

  MyObject () {}

  TracedValue<int32_t> varint;

};


void
intchange (int32_t velho, int32_t novo)
{
    if(novo ==5){
        std::cout << "Traced int " << novo << " from " << velho << std::endl;
    }
}


int
main (int argc, char *argv[])
{   int a;
    int i;
    int j=0;
    int b=0;
  Ptr<MyObject> myObject = CreateObject<MyObject> ();

  // Conectar as sources com as sinks


  myObject->TraceConnectWithoutContext ("MyInteger", MakeCallback (&intchange));



  srand( (unsigned)time(NULL) );
  for(i=1 ; i <= 1000 ; i++) {
        a=rand()%100;
         myObject->varint= a;

         }

}


}
