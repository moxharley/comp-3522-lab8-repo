#include "auctioneer.hpp"
#include <iomanip>

void Auctioneer::register_bidder(Bidder *bidder) {
    bidders.push_back(bidder);
}

void Auctioneer::reset_auctioneer() {
    bidders.clear();
    highest_bid = 0;
    highest_bidder = NULL;
}

void Auctioneer::notify_bidders() {
    for (Bidder *bidder : bidders) {
        if (bidder != highest_bidder) {
            bidder->update(this);
        }
    }
}

void Auctioneer::accept_bid(double bid, Bidder *bidder) {
    string bidder_name = "";
    string highest_bidders_name = "";
    if (bidder == NULL) {
        highest_bid = 100;
        highest_bidder = NULL;
        notify_bidders();
    } else {
        if (highest_bidder == NULL) {
            highest_bidders_name = "Starting bid";
        } else {
            highest_bidders_name = highest_bidder->get_name();
        }
        bidder_name = bidder->get_name();
    }

    if (bid > highest_bid || bid == 100) {
        cout << bidder_name << " bidded $" << 
                fixed << setprecision(2) << bid << " in response to " << 
                highest_bidders_name << "'s bid of $" << 
                highest_bid << endl;
        highest_bid = bid;
        highest_bidder = bidder;
        notify_bidders();
    }
}
