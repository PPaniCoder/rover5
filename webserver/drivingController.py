from flask import Flask
from flask import render_template
import datetime
import logging
import rosDriving

logging.basicConfig(level=logging.DEBUG)
app = Flask(__name__)

templateData = {}

@app.route("/")
def main():
	localtime = datetime.datetime.now()
	strTime = localtime.strftime("%Y-%m-%d %H:%M")

	templateData['title'] = 'Driving Your Life'
	templateData['time'] = strTime

	return render_template('main.html', **templateData)

@app.route("/direction/<value>")
def direction(value):
	logging.debug('direction: %s' % value)
	rosDriving.changeDirection(value)
	return render_template('main.html', **templateData)

@app.route("/speed/<value>")
def speed(value):
	logging.debug('speed: %s' % value)
	rosDriving.changeDirection(value)
	return render_template('main.html', **templateData)


if __name__ == "__main__":
	logging.basicConfig(level=logging.DEBUG)
	rosDriving.setup()
	app.run(host='0.0.0.0', port=21000, debug=True)
