from flask import Flask,render_template
from game_of_life import GameOfLife
 
app = Flask(__name__)

@app.route('/')
def index():
    GameOfLife(25, 25)
    return render_template('index.html')


@app.route('/live')
def live():
    gol = GameOfLife()
    if gol.gen_counter > 0:
        gol.form_new_generation()
    
    gol.gen_counter += 1
    return render_template('live.html',
                           gol_object = gol)

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)