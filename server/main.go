package main

import (
	"time"

	"github.com/astaxie/beego"
	engine "github.com/edot92/smart_door/server/engine"
	_ "github.com/edot92/smart_door/server/routers"
)

func main() {

	// beego.BConfig.Listen.HTTPAddr = "192.168.9.35"
	beego.BConfig.WebConfig.DirectoryIndex = true
	beego.BConfig.CopyRequestBody = true
	beego.BConfig.Listen.HTTPPort = 8080
	beego.BConfig.WebConfig.TemplateLeft = "<%"
	beego.BConfig.WebConfig.TemplateRight = "%>"
	beego.SetStaticPath("/", "webui")
	// beego.SetStaticPath("api", "swagger")
	beego.SetStaticPath("static", "webui/static")
	beego.SetStaticPath("staticpublic/static", "webui/static")
	engine.BukaDatabase()
	go func() {
		beego.Run(":" + beego.AppConfig.String("httpport"))
	}()
	for {
		time.Sleep(100)
	}
}
