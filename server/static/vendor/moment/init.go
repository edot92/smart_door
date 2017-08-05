package controllers

import (
	"flag"
	"github.com/astaxie/beego"
	"os"
	"path/filepath"
)

func init() {
	beego.Debug("Initializing config")
	var config_file string
	flag.StringVar(&config_file, "config", "", "the path of the config file")
	flag.Parse()
	if config_file != "" {
		path, _ := filepath.Abs(config_file)
		beego.Debug("Config params found: ", path)
		beego.AppConfigPath = path
		if err := beego.ParseConfig(); err != nil {
			beego.Error("Config parse error: ", err)
		}
	} else {
		beego.Debug("Config params emtpy. Trying os environment variables")
		if config_file = os.Getenv("BEEGO_APP_CONFIG_FILE"); config_file != "" {
			path, _ := filepath.Abs(config_file)
			beego.Debug("Environment vars found: ", path)
			beego.AppConfigPath = path
			if err := beego.ParseConfig(); err != nil {
				beego.Error("Config parse error: ", err)
			}
		} else {
			beego.Debug("Please pass config params or export BEEGO_APP_CONFIG_FILE variable")
			return
		}
	}
}
