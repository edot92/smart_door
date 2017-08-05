package controllers

import (
	"encoding/json"

	"github.com/astaxie/beego"
	"github.com/edot92/smart_door/server/models"
)

// DeviceController ...
type UserController struct {
	beego.Controller
}

// Getalluser  ...
// @router /getalluser [get]
func (c *UserController) Getalluser() {
	res, err := models.Getalluser()
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil mengambil data user", "data": res}
	}
	c.ServeJSON()
}

// Deleteuserbyid ...
// @router /deleteuserbyid [post]
func (c *UserController) Deleteuserbyid() {
	type paramStruct struct {
		ID int `json:"id"`
	}
	var paramDoor paramStruct
	err := json.Unmarshal(c.Ctx.Input.RequestBody, &paramDoor)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
		c.ServeJSON()
		return
	}
	err = models.Deleteuserbyid(paramDoor.ID)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil menhapus user", "data": nil}
	}
	c.ServeJSON()
}

// Addnewuser ...
// @router /addnewuser [post]
func (c *UserController) AddnewUser() {
	type paramStruct struct {
		Username string `json:"username"`
		Password string `json:"password"`
	}
	var paramDoor paramStruct
	err := json.Unmarshal(c.Ctx.Input.RequestBody, &paramDoor)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
		c.ServeJSON()
		return
	}
	err = models.Addnewuser(paramDoor.Username, paramDoor.Password)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil menambahkan user", "data": nil}
	}
	c.ServeJSON()
}

// Addnewuser ...
// @router /login [post]
func (c *UserController) Login() {
	type paramStruct struct {
		Username string `json:"username"`
		Password string `json:"password"`
	}
	var paramDoor paramStruct
	err := json.Unmarshal(c.Ctx.Input.RequestBody, &paramDoor)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
		c.ServeJSON()
		return
	}
	res, err := models.Login(paramDoor.Username, paramDoor.Password)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil login", "data": res}
	}
	c.ServeJSON()
}
