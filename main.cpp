#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <iomanip>

#include "bidder.hpp"
#include "auction.hpp"

using namespace std;

const double MIN_PROBABILITY = 0;
const double MAX_PROBABILITY = 100;

/*
Returns a random double in [min, max). See Lab-08.pptx for why rand()/RAND_MAX
is used here instead of hardcoding a probability.
*/
double generateRandom(double min, double max)
{
  double f = (double)rand() / RAND_MAX;
  return min + f * (max - min);
}

int main()
{
  srand(time(0));

  vector<Bidder *> bidders;

  // Preloaded test bidders.
  bidders.push_back(new Bidder("Jojo", 3000, generateRandom(MIN_PROBABILITY, MAX_PROBABILITY), 1.2));
  bidders.push_back(new Bidder("Melissa", 7000, generateRandom(MIN_PROBABILITY, MAX_PROBABILITY), 1.5));
  bidders.push_back(new Bidder("Priya", 15000, generateRandom(MIN_PROBABILITY, MAX_PROBABILITY), 1.1));
  bidders.push_back(new Bidder("Kewei", 800, generateRandom(MIN_PROBABILITY, MAX_PROBABILITY), 1.9));
  bidders.push_back(new Bidder("Scott", 4000, generateRandom(MIN_PROBABILITY, MAX_PROBABILITY), 2));

  string item_name;
  double item_price;

  cout << "What is the NAME of the auctioned item?" << endl;
  cin >> item_name;
  cout << "What is the starting PRICE of the auctioned item?" << endl;
  cin >> item_price;

  char yes_no;

  while (true) {
    cout << endl << "Add new bidder? (Y/N)" << endl;
    cin >> yes_no;
    yes_no = toupper(yes_no);

    if (yes_no == 'Y') {
      string name;
      double budget, bid_increase_perc, bid_probability;

      cout << "Name: ";
      cin >> ws;
      getline(cin, name);

      cout << "Budget: $";
      cin >> budget;

      cout << "Bid increase multiplier (1.1, 1.2, 1.25,..): ";
      cin >> bid_increase_perc;

      cout << "Bid probability (0.0 - 1.0): ";
      cin >> bid_probability;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input invalid, bidder not added" << endl;
        continue;
      }

      bidders.push_back(new Bidder(name, budget, bid_probability, bid_increase_perc));
      cout << name << " added" << endl;


    } else if (yes_no == 'N') {
      break;
    } else {
      cout << "Input invalid" << endl;
    }
  }

  cout << "Starting Auction!!" << endl;
  cout << "------------------" << endl;
  Auction my_auction(bidders);
  my_auction.simulate_auction(item_name, item_price);

  for (Bidder *bidder : bidders)
  {
    cout << endl << "Bidder: " << bidder->get_name() << ", Highest Bid: $" << fixed << setprecision(2) << bidder->get_highest() << endl;
    delete bidder;
  }
  return 0;
}
