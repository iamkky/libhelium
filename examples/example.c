#include <stdlib.h>
#include <stdio.h> 
#include "helium/He.h" 

He buildModal_new(char *id, char *title, char *okBttnName, char *cancelBttnName, He content)
{
	return
	heNew("div", heClass("modal fade"), heId(id),
		heAttrNew("tabindex", "-1"),
		heAttrNew("role", "dialog"),
		heAttrNew("aria-labelledby", "modalLabel"),
		heAttrNew("aria-hidden", "true"),
		heNew("div", heClass("modal-dialog"),
			heAttrNew("role", "document"),
			heNew("div", heClass("modal-content"),
				heNew("div", heClass("modal-header"),
					heNew("h5",
						heId("modalLabel"),
						heText(title),
						NULL
					),
					heNew("button",
						heAttrNew("data-dismiss","modal"),
						heAttrNew("aria-label","Close"),
						heNew("span",
							heAttrNew("aria-hidden","true"),
							heText("&times;"),
							NULL
						),
						NULL
					),
					NULL
				),
				heNew("div", heClass("modal-body"),
					content,
					NULL
				),
				heNew("div", heClass("modal-footer"),
					heNew("button",
						heAttrNew("data-dismiss","modal"),
						heText(cancelBttnName),
						NULL
					),
					heNew("button",
						heAttrNew("name", "ok_bttn"),
						heText(okBttnName),
						NULL
					),
					NULL
				),
				NULL
			),
			NULL
		),
		NULL
	);
}
					
