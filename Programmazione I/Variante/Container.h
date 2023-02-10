#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <list>
#include "Box.h"
#include "Box_giacenza.h"

class Container {
    public:
        Container(const int& id=0, const std::string& state="", const std::string& carrier="", const int& nbox=0,
         const int& box_id=0, const double& weight=0.0, const double& value=0.0, const int p=0) 
        : id_container{id}, state_orig{state}, id_carrier{carrier},  n_box{nbox} {
            Box* b = new Box{box_id, weight, value};
            if(p==1){
                b->setPerishable(true);
            } else {
                b->setPerishable(false);
            };
            box.push_front(b);
        };

        double getTotalWeight(){
        double somma{0};
        
        for(std::list<Box*>::const_iterator p=box.begin(); p!=box.end(); ++p){
            somma+=(*p)->getWeight();
        }
    
        return somma;
      }

        double getTotalValue(){
          double somma{0};
  
          for(std::list<Box*>::const_iterator p=box.begin(); p!=box.end(); ++p){
              somma+=(*p)->getValue();
          }
          return somma;
      }

        void addBox(const int& box_id, const double& weight, const double& value, const int p){
            Box* b = new Box{box_id, weight, value};
            if(p==1){
                b->setPerishable(true);
            } else {
                b->setPerishable(false);
            };
            box.push_front(b);
        }

        std::list<BoxGiacenza*> addPersih() {
            std::list<BoxGiacenza*> giacenza;
            for(std::list<Box*>::const_iterator p=box.begin(); p!=box.end(); ++p){
            if((*p)->getPerish()!=true){
                BoxGiacenza* b = new BoxGiacenza{(*p)->getId(),(*p)->getWeight(),(*p)->getValue(),id_container};
                giacenza.push_front(b);
            }   
            }
            return giacenza;
        }

        void removeBox(std::list<BoxGiacenza*> giacenza) {
           
            for(std::list<Box*>::const_iterator b=box.begin(); b!=box.end(); ++b){
                for(std::list<BoxGiacenza*>::const_iterator p=giacenza.begin(); p!=giacenza.end(); ++p){
                    if((*b)->getId() == (*p)->getId()){
                        box.erase(b);
                        n_box=n_box-1;
                    }
                }
            }
        }

    private:
        int n_box;
        std::list<Box*> box;
        int id_container;
        std::string state_orig;
        std::string id_carrier;
};

#endif