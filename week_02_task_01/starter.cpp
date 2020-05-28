#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string operation_code;
	is >> operation_code;

	q.bus = "";
	q.stop = "";
	q.stops.clear();

	if (operation_code == "NEW_BUS")
	{
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (string& stop : q.stops) {
			is >> stop;
		}
	}
	else if (operation_code == "BUSES_FOR_STOP")
	{
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (operation_code == "STOPS_FOR_BUS")
	{
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (operation_code == "ALL_BUSES")
	{
		q.type = QueryType::AllBuses;
	}

	return is;
}

struct BusesForStopResponse {
	std::vector<std::string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.empty())
		os << "No stop" << endl;
	else
	{
		for (const string& bus : r.buses)
			os << bus << " ";
		os << endl;
	}
	return os;
}

struct StopsForBusResponse {
	std::vector<std::string> stops;
	map<string, vector<string>> stops_to_buses;
	string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if(r.stops.empty())
		os << "No bus" << endl;
	else
	{
		for (const string& stop : r.stops) {
			os << "Stop " << stop << ": ";
			if (r.stops_to_buses.at(stop).size() == 1) {
				os << "no interchange";
			}
			else {
				for (const string& other_bus : r.stops_to_buses.at(stop)) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
			}
			os << endl;
		}
	}

	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		os << "No buses" << endl;
	}
	else {
		for (const auto& bus_item : r.buses_to_stops) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}

	return os;
}

class BusManager {
	map<string, vector<string>> buses_to_stops, stops_to_buses;

public:
  void AddBus(const string& bus, const vector<string>& stops) {
	  for (auto& stop : stops)
	  {
		  buses_to_stops[bus].emplace_back(stop);
		  stops_to_buses[stop].emplace_back(bus);
	  }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
	  BusesForStopResponse r;
	  if (stops_to_buses.count(stop) != 0)
		  r.buses = stops_to_buses.at(stop);
	  return r;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
	  StopsForBusResponse r;
	  if (buses_to_stops.count(bus) != 0)
	  {
		  r.stops = buses_to_stops.at(bus);
		  r.bus = bus;
		  r.stops_to_buses = stops_to_buses;
	  }
	  return r;
  }

  AllBusesResponse GetAllBuses() const {
	  AllBusesResponse r;
	  r.buses_to_stops = buses_to_stops;
	  return r;
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
