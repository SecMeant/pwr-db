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
constexpr const char *DB_SCRIPT_INIT_PATH = "../dbinit/base_init.sql";
constexpr const char *DB_SCRIPT_DEP_PATH = "../dbinit/offer_dep_test.sql";
constexpr const char *DB_DATABASE_TEST = "biuro_podrozy_test";

class cOfferModification
{
public:
	cOfferModification()
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
	~cOfferModification(){};
	bool modifiedOffer()
	{
		return hldb_inst.change_offer(o);
	}
  offer_t o;
	char result[32];
  hldb hldb_inst{ DB_DATABASE_TEST };
};

#ifndef CPP_COMPILING
extern "C" {
#endif
typedef struct OfferModification
{
	cOfferModification OfferModification;
	char result[32];
} OfferModification;

void* OfferModification_Create(StatementExecutor* errorHandler, SlimList* args)
{
	OfferModification* self = (OfferModification*)malloc(sizeof(OfferModification));
	self->result[0] = 0;
	return self;
}

void OfferModification_Destroy(void* void_self)
{
	OfferModification* self = (OfferModification*)void_self;
	free(self);
}

static const char* setId(void* void_self, SlimList* args) {
	OfferModification* self = (OfferModification*)void_self;
	self->OfferModification.o.id = atoi(SlimList_GetStringAt(args, 0));
	return self->result;
}
static const char* setName(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.name = SlimList_GetStringAt(args, 0);
  return self->result;
};
static const char* setCountry(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.country = SlimList_GetStringAt(args, 0);
  return self->result;
};
static const char* setCity(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.city = SlimList_GetStringAt(args, 0);
  return self->result;
};
static const char* setDate_begin(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.date_begin =str2epoch(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* setDate_end(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.date_end==str2epoch(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* setPrice(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.price =  atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* setInsurance_cost(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.insurance_cost = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* setExtra_meals_cost(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.extra_meals_cost = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* setCategoryid(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.categoryid = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};
static const char* setTickets_count(void* void_self, SlimList* args)
{
  OfferModification* self = (OfferModification*)void_self;
  self->OfferModification.o.tickets_count = atoi(SlimList_GetStringAt(args, 0));
  return self->result;
};

static const char* ModifiedOffer(void* void_self, SlimList* args) {
	OfferModification* self = (OfferModification*)void_self;
	bool correct = self->OfferModification.modifiedOffer();
	if(correct)
    return "Yes";
  return "No";
}


SLIM_CREATE_FIXTURE(OfferModification)
	SLIM_FUNCTION(setName);
  SLIM_FUNCTION(setCountry);
  SLIM_FUNCTION(setCity);
  SLIM_FUNCTION(setDate_begin);
  SLIM_FUNCTION(setDate_end);
  SLIM_FUNCTION(setPrice);
  SLIM_FUNCTION(setInsurance_cost);
  SLIM_FUNCTION(setExtra_meals_cost);
  SLIM_FUNCTION(setCategoryid);
  SLIM_FUNCTION(setTickets_count);
  SLIM_FUNCTION(ModifiedOffer);
SLIM_END

#ifndef CPP_COMPILING
}
#endif
