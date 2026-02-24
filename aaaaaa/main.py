from flask import Flask
from flask import Response
import requests

app = Flask(__name__)

@app.route('/attribute')
def attribute():
  response = requests.get("https://www.randomnumberapi.com/api/v1.0/random?min=5&max=100")

  return {
    "category": "not_existing_category",
    "attribute": "not_existing_attribute",
    "value": response.json()[0]
  }

@app.route('/discover')
def discover():
  return Response(status = 200)

if __name__ == '__main__':
  app.run(host="0.0.0.0",port=8085)
