# Gallinero

Programa en Arduino para la apertura y cierre automático de un gallinero
en función de la iluminación ambiental.

Se compone de un medidor de luz, un motor paso a paso conectado a la puerta,
varios botones y una placa Arduino.

## Componentes

### Motor paso a paso

NEMA 17HS4401 - A4988
1.7A (12V) 1.5ohm
Voltaje bobina: 1,7*1,15=1,955V
Vref = 1,7 * (8 x 0,1) * 70% = 0.952
1,8º por paso -> 200 pasos por vuelta

### Luxómetro

BH1750

### Placa Arduino

Arduino Micro


```bash
pip install foobar
```

## Usage

```python
import foobar

# returns 'words'
foobar.pluralize('word')

# returns 'geese'
foobar.pluralize('goose')

# returns 'phenomenon'
foobar.singularize('phenomena')
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)