#include "ALL.h";

void task(ALL all)
{
	auto res = all.f1;
	auto res_row = res->h->el;
	double_list* list_1 = all.f2;
	list_1->go_to_start();
	double_list* list_2 = all.f3;
	list_2->go_to_start();

	bool initiated = false;

	while (list_1->c != nullptr) {
		auto list_1_row = list_1->c->el;
		list_1_row->go_to_start();
		while (list_1_row->c != nullptr) {
			if (!list_2->includes(list_1_row->c->el) && !res_row->includes(list_1_row->c->el)) {
				res_row->go_to_start();
				while (res_row->c->get_next() != nullptr) res_row->go_next();

				list_item* new_item = new list_item(list_1_row->c->el);

				if (!initiated) {
					initiated = true;

					double_list_item* new_row = new double_list_item(new list(new_item));
					new_row->el->go_to_start();
					res->h = new_row;
					res->go_to_start();
					res_row = res->h->el;
				}
				else {
					res_row->c->set_next(new_item);
				}
			}

			list_1_row->go_next();
		}
		list_1->go_next();
	}
}
