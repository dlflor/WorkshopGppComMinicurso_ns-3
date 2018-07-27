/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/object.h"
#include "ns3/uinteger.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"

#include <iostream>

using namespace ns3;

// Para criar multiplos trace sources:
// - Criar uma classe hedando da classe "Object" do ns3
// - Definir o metodo typeId no escopo publico conforme abaixo
// - Atribuir os valores a TypeId confomre abaixo
// - .AddTraceSource("Nome_do Source","String de Help",
//    MakeTraceSourceAccessor (&SeuObjeto::seuMembro),
//    ns3::TarcedValueCallback:tipo)
// - Os tipos e como sao escritos sao definidos em traced-value.h
// - Para multiplos sources, utilizar multiplos .AddTraceSource
// - Criar os membros da classe definidos no .AddTraceSource usando
//   TracedValue<tipo> membro

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
      .AddTraceSource ("MyDouble",
                       "A Double value to trace.",
                       MakeTraceSourceAccessor (&MyObject::pastel),
                       "ns3::TracedValueCallback::Double")
      .AddTraceSource ("MyInteger",
                       "An integer value to trace.2",
                       MakeTraceSourceAccessor (&MyObject::pastel2),
                       "ns3::TracedValueCallback::Int32")
    ;

    return tid;
	}

  MyObject () {}
  TracedValue<double> pastel;
  TracedValue<int32_t> pastel2;
};

// Definir funcao de Sink
// Funcao pode ter qualquer norme nao resevado
// Ver traced-callback.h para os templates
// Prestar atencao na forma do argumento e nos tipos
// Multiplas sinks podem ser conectadas ao mesmo source/
// Nomes dos argumentos podem ser quaisquer

void
BomDia (double oldValue, double newValue)
{
  std::cout << "Traced " << oldValue << " to " << newValue << std::endl;
}

void
BoaTarde (double oldValue, double newValue)
{
  std::cout << "Rastreado " << oldValue << " para " << newValue << std::endl;
}

void
BoaNoite (int32_t velho, int32_t novo)
{
  std::cout << "Traced " << novo << " from " << velho << std::endl;
}


int
main (int argc, char *argv[])
{
  Ptr<MyObject> myObject = CreateObject<MyObject> ();

  // Conectar as sources com as sinks

  myObject->TraceConnectWithoutContext ("MyDouble", MakeCallback (&BomDia));
  myObject->TraceConnectWithoutContext ("MyDouble", MakeCallback (&BoaTarde));
  myObject->TraceConnectWithoutContext ("MyInteger", MakeCallback (&BoaNoite));

  myObject->pastel = 42.42;
  myObject->pastel2 = 73;
  



}
