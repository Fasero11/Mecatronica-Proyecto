import serial
from music21 import converter, instrument, note, stream, chord
import mido
import sys

def check_arg():
    # Lee los argumentos de la línea de comandos
    argument = sys.argv[1:]

    if len(argument) != 1:
        print("Error: only 1 song needed")
        sys.exit(1)
    else:
        return argument[0]

def midi_to_notes(file_path):

    midi = converter.parse(file_path)
    notes_to_parse = None

    try: # File has instrument parts
        s2 = instrument.partitionByInstrument(midi)
        notes_to_parse = s2.parts[0].recurse() 
    except: # File has notes in a flat structure
        notes_to_parse = midi.flat.notes

    notes = []
    for element in notes_to_parse:
        if isinstance(element, note.Note):
            notes.append(element.pitch.nameWithOctave)
        elif isinstance(element, chord.Chord):
            notes.append('.'.join(n.pitch.nameWithOctave for n in element.notes))

    return notes

def convert_to_clave_de_sol(notes):
    # Convertir las notas a la notación de la clave de sol en español
    converted_notes = []
    notes_diccionary = {"C": "Do", "D": "Re", "E": "Mi", "F": "Fa", "G": "Sol", "A": "La", "B": "Si"}

    for n in notes:
        note, octave = n[:-1], n[-1] if n[-1].isdigit() else n[-2:]
        if note in notes_diccionary:
            converted_notes.append(notes_diccionary[note] + octave)

    return converted_notes

def convert_clave_sol_to_numbers(notes):
    # Asignar números a las notas en función de la tabla de equivalencia
    equivalence_table = {
        'Do0': 1,  'Do#0': 2,  'Re0': 19, 'Re#0': 20, 'Mi0': 37, 'Fa0': 46, 'Fa#0': 47, 'Sol0': 64, 'Sol#0': 65, 'La0': 82, 'La#0': 83, 'Si0': 100,
        'Do1': 3,  'Do#1': 4,  'Re1': 21, 'Re#1': 22, 'Mi1': 38, 'Fa1': 48, 'Fa#1': 49, 'Sol1': 66, 'Sol#1': 67, 'La1': 84, 'La#1': 85, 'Si1': 101,
        'Do2': 5,  'Do#2': 6,  'Re2': 23, 'Re#2': 24, 'Mi2': 39, 'Fa2': 50, 'Fa#2': 51, 'Sol2': 68, 'Sol#2': 69, 'La2': 86, 'La#2': 87, 'Si2': 102,
        'Do3': 7,  'Do#3': 8,  'Re3': 25, 'Re#3': 26, 'Mi3': 40, 'Fa3': 52, 'Fa#3': 53, 'Sol3': 70, 'Sol#3': 71, 'La3': 88, 'La#3': 89, 'Si3': 103,
        'Do4': 9,  'Do#4': 10, 'Re4': 27, 'Re#4': 28, 'Mi4': 41, 'Fa4': 54, 'Fa#4': 55, 'Sol4': 72, 'Sol#4': 73, 'La4': 90, 'La#4': 91, 'Si4': 104,
        'Do5': 11, 'Do#5': 12, 'Re5': 29, 'Re#5': 30, 'Mi5': 42, 'Fa5': 56, 'Fa#5': 57, 'Sol5': 74, 'Sol#5': 75, 'La5': 92, 'La#5': 93, 'Si5': 105,
        'Do6': 13, 'Do#6': 14, 'Re6': 31, 'Re#6': 32, 'Mi6': 43, 'Fa6': 58, 'Fa#6': 59, 'Sol6': 76, 'Sol#6': 77, 'La6': 94, 'La#6': 95, 'Si6': 106,
        'Do7': 15, 'Do#7': 16, 'Re7': 33, 'Re#7': 34, 'Mi7': 44, 'Fa7': 60, 'Fa#7': 61, 'Sol7': 78, 'Sol#7': 79, 'La7': 96, 'La#7': 97, 'Si7': 107,
        'Do8': 17, 'Do#8': 18, 'Re8': 35, 'Re#8': 36, 'Mi8': 45, 'Fa8': 62, 'Fa#8': 63, 'Sol8': 80, 'Sol#8': 81, 'La8': 98, 'La#8': 99, 'Si8': 108
    }
    
    converted_notes = []
    for note in notes:
        if note in equivalence_table:
            converted_notes.append(equivalence_table[note])
    return converted_notes

def extract_tempo(file_path):
    mid = mido.MidiFile(file_path)
    for track in mid.tracks:
        for msg in track:
            if msg.type == 'set_tempo':
                tempo = mido.tempo2bpm(msg.tempo)
                return tempo
    return None
    

# Usage
file_path = check_arg()
notes = midi_to_notes(file_path)
notes_clave_sol = convert_to_clave_de_sol(notes)
print(notes_clave_sol)
notas_numeros = convert_clave_sol_to_numbers(notes_clave_sol)
print(notas_numeros)

tempo = extract_tempo(file_path)
if tempo:
    print(f"El tempo del archivo MIDI es: {tempo} BPM")
else:
    print("No se encontró información de tempo en el archivo MIDI.")

#notes_message = tempo + notas_numeros
tempo_msg = "Tempo: " + str(tempo)
print(tempo_msg)


# Abre la conexión con el puerto serie
#ser = serial.Serial('/dev/ttyUSB0', 9600)  # Ajusta '/dev/ttyUSB0' al puerto correcto de tu Arduino 
#print(notes_clave_sol)
## Envía datos a Arduino
#ser.write(tempo_msg.encode())
## Cierra la conexión
#ser.close()
#
