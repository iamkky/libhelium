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
					
					
/*
HtElement buildModal_Old(TmCgi c, char *id, char *title, char *okBttnName, char *cancelBttnName, HtElement content)
{
	divModal = htDiv("modal fade",
			divModalDialog = htDiv("modal-dialog",
				htDiv("modal-content",
					htDiv("modal-header",
						modalTitle = htH5Str("modal-title", title),
						closeBttn = htButton2("close")
					),
					htDiv("modal-body", content),
					htDiv("modal-footer",
						cancelBttn = htButton2("btn btn-secondary"),
						saveBttn = htButton2("btn btn-primary")
					)
				)
			)
		);

	closeBttn->add(closeBttn,
		att1 = htSpan(NULL, htText("&times;"))
	);

	cancelBttn->add(cancelBttn, htText(cancelBttnName));
	htElementAddAttribute(cancelBttn, htAttributeNew("data-dismiss","modal"));

	saveBttn->add(saveBttn, htText(okBttnName));
	htElementAddAttribute(saveBttn, htAttributeNew("name", "ok_bttn"));

	htElementAddAttribute(att1, htAttributeNew("aria-hidden","true"));

	snprintf(attributes, sizeof(attributes), "id:%s,tabindex:-1,role:dialog,aria-labelledby:modalLabel,aria-hidden:true", id);
	htElementAddAttributeInBatch(divModal, NULL, attributes);
	htElementAddAttribute(divModalDialog, htAttributeNew("role", "document"));
	htElementAddAttribute(modalTitle, htAttributeNew("id", "modalLabel"));
	htElementAddAttributeInBatch(closeBttn, NULL, "data-dismiss:modal,aria-label:Close");

	return divModal;
}
*/

int main(int argc, char **argv)
{
StringBuffer output;
He e;

	e = buildModal_new("the_id", "this_is_the_title", "ok_button", "cancel_button", 
		heNew("div", heClass("content"),
			heText("Content"),
			heNew("img",
				heAttrNew("src", "teste.gif"),
				NULL
			),
			NULL
		)
	);
	output = StringBufferNew(512);
	heRender(e, output);

	puts(stringBufferGetBuffer(output));

}
