extern "C"{
#include <CSlim/SlimList.h>
#include <CSlim/Fixtures.h>
#include <CSlim/compatibility.h>
}
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fmt/format.h>
#include "hldb.h"
#include <string>
#include <fstream>

using namespace std;
using namespace app::logic;
using namespace app::dbaccess;
constexpr const char *DB_SCRIPT_INIT_PATH = "/home/windspring/git_repos/pwr-db/dbinit/base_init.sql";
constexpr const char *DB_SCRIPT_DEP_PATH = "/home/windspring/git_repos/pwr-db/dbinit/offer_dep_test.sql";
constexpr const char *DB_DATABASE_TEST = "biuro_podrozy_test";

class cOffermodification
{
public:
	cOffermodification()
  {
    if (!hldb_inst.m_dbconn) {
      exit(1);
    }

    std::fstream fs(DB_SCRIPT_INIT_PATH, std::fstream::in);

    if (!fs.is_open()) {
      exit(1);
    }
    std::string query;
    while (std::getline(fs, query, ';')) {
      if (query == "") {
        continue;
      }
      if (hldb_inst.m_dbconn.query(query.c_str()) == false) {
        exit(1);
      }
    }
    fs.close();
    fs.open(DB_SCRIPT_DEP_PATH, std::fstream::in);

    if (!fs.is_open()) {
      exit(1);
    }
    while (std::getline(fs, query, ';')) {
      if (query == "" || query == "\n") {
        continue;
      }
      if (hldb_inst.m_dbconn.query(query.c_str()) == false) {
        exit(1);
      }
    }
  }
	~cOffermodification(){};
	bool modifieOffer()
	{
		return hldb_inst.change_offer(o);
	}
  bool dropOffer()
  {
    return hldb_inst.drop_offer(o);
  }
  offer_t o;
	char result[32];
  hldb hldb_inst{ DB_DATABASE_TEST };
};

#ifndef CPP_COMPILING
extern "C" {
#endif
typedef struct Offermodification
{
	cOffermodification Offermodification;
	char result[32];
} Offermodification;

void* Offermodification_Create(StatementExecutor* errorHandler, SlimList* args)
{
	// Offermodification* self = (Offermodification*)malloc(sizeof(Offermodification));
  Offermodification* self = new Offermodification;
	self->result[0] = 0;
	return self;
}

void Offermodification_Destroy(void* void_self)
{
	Offermodification* self = (Offermodification*)void_self;
	// free(self);
  delete self;
}

static const char* set_Offer_id(void* void_self, SlimList* args) {
	Offermodification* self = (Offermodification*)void_self;
	self->Offermodification.o.id = atoi(SlimList_GetStringAt(args, 0));
	return self->result;
}
static const char* set_Offer_name(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.name =SlimList_GetStringAt(args, 0);
  return self->result;
};
static const char* set_Offer_country(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  const char * asdf = SlimList_GetStringAt(args, 0);
  self->Offermodification.o.country = SlimList_GetStringAt(args, 0);
  return self->result;
};
static const char* set_Offer_city(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.city = SlimList_GetStringAt(args, 0);
  return self->result;
};
static const char* set_Offer_date_begin(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.date_begin =str2epoch(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* set_Offer_date_end(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.date_end==str2epoch(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* set_Offer_price(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.price =  atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* set_Offer_insurance_cost(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.insurance_cost = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* set_Offer_extra_meals_cost(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.extra_meals_cost = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* set_Offer_categoryid(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.categoryid = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* set_Offer_tickets_count(void* void_self, SlimList* args)
{
  Offermodification* self = (Offermodification*)void_self;
  self->Offermodification.o.tickets_count = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};

static const char* offer_Modified(void* void_self, SlimList* args) {
	Offermodification* self = (Offermodification*)void_self;
	bool res = self->Offermodification.modifieOffer();
	if(res)
    return "Yes";
  return "No";
}

static const char* offer_Removed(void* void_self, SlimList* args) {
  Offermodification* self = (Offermodification*)void_self;
  bool res = self->Offermodification.dropOffer();
  if(res)
    return "Yes";
  return "No";
}

SLIM_CREATE_FIXTURE(Offermodification)
	SLIM_FUNCTION(set_Offer_id);
  SLIM_FUNCTION(set_Offer_name);
  SLIM_FUNCTION(set_Offer_country);
  SLIM_FUNCTION(set_Offer_city);
  SLIM_FUNCTION(set_Offer_date_begin);
  SLIM_FUNCTION(set_Offer_date_end);
  SLIM_FUNCTION(set_Offer_price);
  SLIM_FUNCTION(set_Offer_insurance_cost);
  SLIM_FUNCTION(set_Offer_extra_meals_cost);
  SLIM_FUNCTION(set_Offer_categoryid);
  SLIM_FUNCTION(set_Offer_tickets_count);
  SLIM_FUNCTION(offer_Modified);
  SLIM_FUNCTION(offer_Removed);
SLIM_END

#ifndef CPP_COMPILING
}
#endif
