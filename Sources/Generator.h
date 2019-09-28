/*
 * Generator.h
 *
 * Clock Generator Module
 */
#ifndef SOURCES_GENERATOR_H_
#define SOURCES_GENERATOR_H_

static constexpr unsigned MIN_FREQUENCY = 5;
static constexpr unsigned MAX_FREQUENCY = 2000001;

/**
 * Initialise the generator before first use
 */
void generatorInitialise();

/**
 * Set generator Frequency
 *
 * @param frequency [MIN_FREQUENCY ... MAX_FREQUENCY]
 */
void generatorSetFrequency(unsigned frequency);
void outputOff();

#endif /* SOURCES_GENERATOR_H_ */
