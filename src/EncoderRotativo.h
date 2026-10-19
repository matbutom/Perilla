#ifndef ENCODER_ROTATIVO_H
#define ENCODER_ROTATIVO_H

#include <stdint.h>

/**
 * \~spanish
 * @brief Lee un encoder rotativo incremental en CLK y DT, con boton SW opcional.
 *
 * Es independiente de Perilla, que conserva su comportamiento previo para
 * potenciometros. Llame actualizar() frecuentemente en cada vuelta del loop:
 * el encoder se sondea y una transicion ocurrida entre lecturas puede perderse.
 * Las entradas usan pull-up interno y se conectan al comun del encoder.
 *
 * \~english
 * @brief Reads an incremental rotary encoder on CLK and DT, with optional SW button.
 *
 * It is independent of Perilla, which keeps its previous potentiometer behavior.
 * Call actualizar() frequently on every loop iteration: the encoder is polled
 * and a transition between reads can be missed. Inputs use internal pull-ups
 * and connect to the encoder common terminal.
 */
class EncoderRotativo
{
public:
    /**
     * \~spanish
     * @brief Direccion del ultimo paso detectado por actualizar().
     * \~english
     * @brief Direction of the last step detected by actualizar().
     */
    enum Direccion { QUIETA, HORARIO, ANTIHORARIO };

    /**
     * \~spanish
     * @brief Crea el encoder y configura CLK, DT y opcionalmente SW como entradas pull-up.
     * @param pinCLK pin CLK.
     * @param pinDT pin DT.
     * @param pinSW pin SW; usa -1 si no hay boton.
     *
     * \~english
     * @brief Creates the encoder and configures CLK, DT and optional SW as pull-up inputs.
     * @param pinCLK CLK pin.
     * @param pinDT DT pin.
     * @param pinSW SW pin; use -1 when there is no button.
     */
    EncoderRotativo(uint8_t pinCLK, uint8_t pinDT, int16_t pinSW = -1);

    /**
     * \~spanish
     * @brief Sondea encoder y boton; llamar frecuentemente, sin demoras largas en el loop.
     * @return true si cambio la posicion.
     * \~english
     * @brief Polls encoder and button; call frequently without long delays in the loop.
     * @return true if the position changed.
     */
    bool actualizar();

    /**
     * \~spanish
     * @brief Sentido del ultimo paso visto; QUIETA si no hubo paso en la lectura.
     * \~english
     * @brief Direction of the last observed step; QUIETA if this poll had no step.
     */
    Direccion getDireccion() const;

    /**
     * \~spanish
     * @brief Posicion firmada actual.
     * @return posicion positiva o negativa.
     * \~english
     * @brief Current signed position.
     * @return positive or negative position.
     */
    int32_t getPosicion() const;

    /**
     * \~spanish
     * @brief Establece la posicion sin cambiar el estado de cuadratura.
     * @param nuevaPosicion nueva posicion.
     * \~english
     * @brief Sets the position without changing the quadrature state.
     * @param nuevaPosicion new position.
     */
    void setPosicion(int32_t nuevaPosicion);

    /**
     * \~spanish
     * @brief Configura cuantas transiciones validas forman un paso; por defecto 4.
     * @param transiciones valor de 1 a 4; otros valores se limitan al rango.
     * \~english
     * @brief Sets the valid transitions per step; defaults to 4.
     * @param transiciones value from 1 to 4; other values are clamped.
     */
    void setTransicionesPorPaso(uint8_t transiciones);

    /**
     * \~spanish
     * @brief Invierte el signo del siguiente giro.
     * @param invertir true para invertir.
     * \~english
     * @brief Reverses the sign of the next turn.
     * @param invertir true to reverse.
     */
    void setInvertido(bool invertir);

    /**
     * \~spanish
     * @brief Configura el antirrebote del boton, en milisegundos (por defecto 25).
     * @param milisegundos duracion de estabilidad requerida.
     * \~english
     * @brief Sets button debounce time in milliseconds (25 by default).
     * @param milisegundos required stable duration.
     */
    void setAntirrebote(uint16_t milisegundos);

    /**
     * \~spanish
     * @brief Estado estable del boton; true cuando SW esta presionado.
     * @return estado del boton.
     * \~english
     * @brief Stable button state; true while SW is pressed.
     * @return button state.
     */
    bool getBotonPresionado() const;

    /**
     * \~spanish
     * @brief Devuelve true una sola vez al detectar una nueva pulsacion estable.
     * @return evento de pulsacion pendiente.
     * \~english
     * @brief Returns true once when a new stable press is detected.
     * @return pending press event.
     */
    bool fuePresionado();

    /**
     * \~spanish
     * @brief Devuelve true una sola vez al detectar una liberacion estable.
     * @return evento de liberacion pendiente.
     * \~english
     * @brief Returns true once when a stable release is detected.
     * @return pending release event.
     */
    bool fueLiberado();

private:
    uint8_t pinCLK;
    uint8_t pinDT;
    int16_t pinSW;
    uint8_t estadoAnterior;
    int8_t avance;
    int32_t posicion;
    uint8_t transicionesPorPaso;
    Direccion direccion;
    bool invertido;
    uint16_t antirreboteMs;
    bool botonLectura;
    bool botonEstable;
    uint32_t cambioBotonMs;
    bool eventoPresionado;
    bool eventoLiberado;
};

#endif
