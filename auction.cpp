#include "auction.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Auction::Auction(vector<Bidder *> bidders) {
    for (Bidder *bidder : bidders) {
        auctioneer.register_bidder(bidder);
    }
}

void Auction::simulate_auction(string item, double start_price) {
    cout << "Auctioning " << item << " at starting price $" << start_price << endl;
    auctioneer.accept_bid(start_price, nullptr);
    
    Bidder *winner = auctioneer.get_highest_bidder();
    double winning_bid = auctioneer.get_highest_bid();

    cout << fixed << setprecision(2) << endl << "The " << item << " goes to " << winner->get_name() << " for $" << winning_bid << endl;
}
