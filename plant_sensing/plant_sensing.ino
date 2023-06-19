#define SET_BIT(x, y) (x |= (1 << y))
#define CLR_BIT(x, y) (x &= ~(1 << y))
#define CHK_BIT(x, y) (x & (1 << y))
#define TOG_BIT(x, y) (x ^= (1 << y))

const int NUM_SAMPLES = 160;
float results[NUM_SAMPLES];
float freq[NUM_SAMPLES];

void setup()
{
    TCCR1A = 0b10000010;
    TCCR1B = 0b00011001;
    ICR1 = 110;
    OCR1A = 55;

    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);

    Serial.begin(115200);

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        results[i] = 0;
        freq[i] = i;
    }
}

void loop()
{
    for (unsigned int d = 0; d < NUM_SAMPLES; d++)
    {
        int v = analogRead(0);

        CLR_BIT(TCCR1B, 0);
        TCNT1 = 0;
        ICR1 = d;
        OCR1A = d / 2;
        SET_BIT(TCCR1B, 0);

        results[d] = results[d] * 0.5 + (float)(v) * 0.5; 
        Serial.println(results[d]);

        delayMicroseconds(1);
    }

    TOG_BIT(PORTB, 0); 
}
