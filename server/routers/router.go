package routers

// @APIVersion 1.0.0
// @Title beego Test API
// @Description beego has a very cool tools to autogenerate documents for your API
// @Contact astaxie@gmail.com
// @TermsOfServiceUrl http://beego.me/
// @License Apache 2.0
// @LicenseUrl http://www.apache.org/licenses/LICENSE-2.0.html
import (
	"github.com/astaxie/beego"
	"github.com/astaxie/beego/plugins/cors"
	"github.com/edot92/smart_door/server/controllers"
)

func init() {
	// CORS for https://foo.* origins, allowing:
	// - PUT and PATCH methods
	// - Origin header
	// - Credentials share
	beego.InsertFilter("/*", beego.BeforeRouter, cors.Allow(&cors.Options{
		// AllowAllOrigins: true,
		// AllowMethods:    []string{"GET", "POST", "PUT", "DELETE", "OPTIONS"},
		// AllowHeaders:    []string{"Origin", "Authorization", "Access-Control-Allow-Origin"},
		// ExposeHeaders:   []string{"Content-Length", "Access-Control-Allow-Origin"},
		AllowAllOrigins:  true,
		AllowMethods:     []string{"GET", "POST", "PUT", "DELETE", "OPTIONS"},
		AllowHeaders:     []string{"Origin", "Authorization", "authorization", "Access-Control-Allow-Origin", "Content-Type", "X-CSRF-TOKEN"},
		ExposeHeaders:    []string{"Content-Length", "Access-Control-Allow-Origin"},
		AllowCredentials: true,
		AllowOrigins:     []string{"https://127.0.0.1/:5003", "http://localhost:8081", "http://localhost:8888", "http://192.168.0.103:8080", "http://192.168.0.103:8081"},
	}))
	// beego.Router("/", &controllers.MainController{})
	ns := beego.NewNamespace("/v1",
		beego.NSNamespace("/device",
			beego.NSInclude(
				&controllers.DeviceController{},
			),
		),
		beego.NSNamespace("/mikro",
			beego.NSInclude(
				&controllers.MikroController{},
			),
		),
		beego.NSNamespace("/email",
			beego.NSInclude(
				&controllers.EmailController{},
			),
		),
		beego.NSNamespace("/user",
			beego.NSInclude(
				&controllers.UserController{},
			),
		),
	)
	beego.AddNamespace(ns)
}
