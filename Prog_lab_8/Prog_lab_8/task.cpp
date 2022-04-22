#include "ALL.h";

void task(ALL all)
{
	double_list* res = all.f1;
	double_list* m1 = all.f2;
	double_list* m2 = all.f3;

	list* frowr = res->c->el;
	frowr->go_to_start();
	list* frow1 = m1->h->el;
	frow1->go_to_start();
	list* frow2 = m2->h->el;

	bool initiated = false;

	while (frow1->c != nullptr) {
		if (!frow2->includes(frow1->c->el) && !frowr->includes(frow1->c->el)) {
			frowr->go_to_start();
			while (frowr->c->get_next() != nullptr) frowr->go_next();

			list_item* new_item = new list_item(frow1->c->el);

			if (!initiated) {
				initiated = true;

				double_list_item* new_row = new double_list_item(new list(new_item));
				new_row->el->go_to_start();
				res->h = new_row;
				res->go_to_start();
				frowr = res->h->el;
			}
			else {
				frowr->c->set_next(new_item);
			}
		}

		frow1->go_next();
	}
}
