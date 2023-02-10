#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <list>
#include <vector>
#include "Queue.h"
#include "Container.h"
#include "Box.h"
#include "Box_giacenza.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ios;
using std::setw;
using std::invalid_argument;

void add(ifstream&, LinkedQueue<Container>&);
void clearance(ifstream&, LinkedQueue<Container>&);
void addeletePerish(ifstream&, LinkedQueue<Container>&, std::list<BoxGiacenza*>&);

int main() {
  ifstream f{"containers.txt", ios::in};
  if(!f){
      std::cerr << "File could not be open." << endl;
      exit(EXIT_FAILURE);
  }
  LinkedQueue<Container> c;
  std::list<BoxGiacenza*> giacenza;
	add(f, c);
  clearance(f, c);
  addeletePerish(f, c, giacenza);

  f.close();
}

void clearance(ifstream& f, LinkedQueue<Container>& c) {
  for (int i = 0; i < c.size(); i++)
  { 
    cout << "-- Peso e il valore Totale del container " << i << " --" << endl;
    cout << c[i].getTotalWeight() << endl;
    cout << c[i].getTotalValue() << endl;
  }
}

void add(ifstream& f, LinkedQueue<Container>& c){
  int id_container;
  string state_orig;
  string id_carrier;
  int n_box;
  int box_id;
  double weight;
  double value;
  int perishable;
  f.seekg(0,ios::beg);

  while(f >> id_container >> state_orig >> id_carrier >> n_box >> box_id >> weight >> value >> perishable){
    Container container{id_container, state_orig, id_carrier, n_box, box_id, weight, value, perishable};
    for (int i = 0; i < n_box-1; i++){
      f >> box_id >> weight >> value >> perishable;
      container.addBox(box_id, weight, value, perishable);
    }
    c.enqueue(container);
  }
}

void addeletePerish(ifstream& f, LinkedQueue<Container>& c, std::list<BoxGiacenza*>& giacenza) {
  int k;
  for (int i = 0; i < c.size(); i++)
  { 
    if (c[i].getTotalValue() > 2600.0){
      cout << "Il conteiner " << i << "supera il valore di 2600 !" << endl;
      k = i;
    }
  }
  giacenza = c[k].addPersih();
  c[k].removeBox(giacenza);
}
