#include "auction.hpp"
#include <iostream>

using namespace std;

Auction::Auction(vector<Bidder *> bidders) {
    for (Bidder *bidder : bidders) {
        auctioneer.register_bidder(bidder);
    }
}

void Auction::simulate_auction(string item, double start_price) {
    // TODO: announce the item and starting price, then place the opening
    // bid via auctioneer.accept_bid(start_price) to kick off the chain of
    // notifications (see README for the observer flow this triggers).
    // Once the chain settles, print the winner (auctioneer's highest
    // bidder/bid) and a per-bidder summary of each bidder's highest bid.
    cout << "Auctioning " << item << " at starting price $" << start_price << endl;
    auctioneer.accept_bid(start_price);
    cout << endl << "Winning message goes here." << endl;
}
