#include "cards.hh"
#include <iostream>

using namespace std;

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr) {
}

Cards::~Cards() {
   while ( top_ != nullptr ) {
      Card_data* item_to_be_released = top_;
      top_ = top_->next;

      delete item_to_be_released;
   }
}


void Cards::add(int id){
    Card_data* new_card = new Card_data{id, top_};
    top_= new_card;
}


void Cards::print_from_top_to_bottom(std::ostream& s){
    Card_data* item_to_be_printed = top_;
    int running_number = 1;

    while ( item_to_be_printed != nullptr) {
       s << running_number << ": " << item_to_be_printed->data << endl;
       ++running_number;
       item_to_be_printed = item_to_be_printed->next;
    }
}

bool Cards::remove(int &id){
    if ( top_ == nullptr ) {
       return false;
    }

    Card_data* item_to_be_removed = top_;

    id = item_to_be_removed->data;

    if ( top_->next == nullptr ) {
       top_ = nullptr;
    } else {
       top_ = top_->next;
    }

    delete item_to_be_removed;

    return true;

}

bool Cards::bottom_to_top(){
    if ( top_ == nullptr ) {
       return false;
    }

    if ( top_->next == nullptr ) {
        return true;
    }

    Card_data* second_last = top_;

        while(second_last->next->next != nullptr){
            second_last = second_last->next;
        }
        Card_data* last = second_last->next;
        last->next = top_;
        top_ = last;
        second_last->next = nullptr;

        return true;
}

bool Cards::top_to_bottom(){

    if(top_ == nullptr){
        return false;
    }
    Card_data* last = top_;
    while(last->next != nullptr){
        last = last->next;
    }
    last->next = top_;
    top_ = top_->next;
    last->next->next = nullptr;

    return true;

}

void Cards::print_from_bottom_to_top(ostream& s){
    recursive_print(top_,s);

}

int Cards::recursive_print(Cards::Card_data* current, std::ostream &s)
{
    if(current == nullptr){
        return 1;
    }

    int number = recursive_print(current->next, s);
    s << number << ": " << current->data << std::endl;
    return number +1;

}



