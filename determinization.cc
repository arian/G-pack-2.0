
#include "problems.h"

void determinizeSingleOutcome(std::ostream &os, problem_t *p)
{
  os << "(define (problem " << p->name() << ") ";
  os << "(:domain " << p->domain().name() << ") ";
  os << "(:objects";

  for(Object i = p->terms().first_object(); i <= p->terms().last_object(); ++i) {
    os << std::endl << " ";
    p->terms().print_term( os, i );
    os << " - ";
    p->domain().types().print_type( os, p->terms().type( i ) );
  }
  os << std::endl << ")" << std::endl;

  os << "(:init ";
  for (AtomSet::const_iterator ai = p->init_atoms().begin(); ai != p->init_atoms().end(); ++ai) {
    os << std::endl << " ";
    (*ai)->print(os, p->domain().predicates(), p->domain().functions(), p->terms());
  }

  // Find absorbing states
  os << std::endl << "actions" << std::endl;
  for (ActionList::const_iterator ai = p->actions().begin(); ai != p->actions().end(); ++ai) {
    (*ai)->print(os, p->terms());
    os << std::endl << "effect" << std::endl;
    (*ai)->effect().print(os, p->domain().predicates(), p->domain().functions(), p->terms());
    os << std::endl;
  }

  os << std::endl << ")" << std::endl;
}
