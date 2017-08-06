package routers

import (
	"github.com/astaxie/beego"
	"github.com/astaxie/beego/context/param"
)

func init() {

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:DeviceController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:DeviceController"],
		beego.ControllerComments{
			Method: "Getlastvalue",
			Router: `/getlastvalue`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:DeviceController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:DeviceController"],
		beego.ControllerComments{
			Method: "Updatevalue",
			Router: `/updatevalue`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:EmailController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:EmailController"],
		beego.ControllerComments{
			Method: "Addnewemail",
			Router: `/addnewemail`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:EmailController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:EmailController"],
		beego.ControllerComments{
			Method: "Deleteemailbyid",
			Router: `/deleteemailbyid`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:EmailController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:EmailController"],
		beego.ControllerComments{
			Method: "Getallemail",
			Router: `/getallemail`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:MikroController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:MikroController"],
		beego.ControllerComments{
			Method: "Getlastvalue",
			Router: `/getlastvalue`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:MikroController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:MikroController"],
		beego.ControllerComments{
			Method: "Updateclosealldoor",
			Router: `/updateclosealldoor`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:MikroController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:MikroController"],
		beego.ControllerComments{
			Method: "UpdatelogAlat",
			Router: `/updatelogalat`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"],
		beego.ControllerComments{
			Method: "AddnewUser",
			Router: `/addnewuser`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"],
		beego.ControllerComments{
			Method: "Deleteuserbyid",
			Router: `/deleteuserbyid`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"],
		beego.ControllerComments{
			Method: "Getalluser",
			Router: `/getalluser`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"] = append(beego.GlobalControllerRouter["github.com/edot92/smart_door/server/controllers:UserController"],
		beego.ControllerComments{
			Method: "Login",
			Router: `/login`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

}
