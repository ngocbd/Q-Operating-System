#include "sort.h"

char *words[10][50] = {
    {   // Unknown Words
        "UNKNOWN UNKNOWN"
    },
    {   // Nouns
        "NOUN UNKNOWN",
        "NOUN ACT",
        "NOUN ANIMAL",
        "NOUN ARTIFACT",
        "NOUN ATTRIBUTE",
        "NOUN BODY",
        "NOUN COGNITION",
        "NOUN COMMUNICATION",
        "NOUN EVENT",
        "NOUN FEELING",
        "NOUN FOOD",
        "NOUN GROUP",
        "NOUN LOCATION",
        "NOUN MOTIVE",
        "NOUN OBJECT",
        "NOUN PERSON",
        "NOUN QUANTITY",
        "NOUN RELATION",
        "NOUN SHAPE",
        "NOUN STATE",
        "NOUN SUBSTANCE",
        "NOUN TOPS",
    },
    {   // Verbs
        "VERB UNKNOWN",
        "VERB BODY",
        "VERB CHANGE",
        "VERB COGNITION",
        "VERB COMMUNICATION",
        "VERB COMPETITION",
        "VERB CONSUMPTION",
        "VERB CONTACT",
        "VERB CREATION",
        "VERB EMOTION",
        "VERB FRAMESTEXT",
        "VERB MOTION",
        "VERB PERCEPTION",
        "VERB POSSESSION",
        "VERB SOCIAL",
        "VERB STATIVE",
        "VERB WEATHER",
    },
    {   // Adjectives
        "ADJECTIVE UNKNOWN"
    },
    {   // Interjections
        "ADVERB UNKNOWN"
    },
    {   // cONJUNCTIONS
        "CONJUNCTION UNKNOWN",
        "CONJUNCTION COMPARISON",
        "CONJUNCTION CONCESSION",
        "CONJUNCTION CONDITION",
        "CONJUNCTION COORDINATING",
        "CONJUNCTION MANNER",
        "CONJUNCTION PLACE",
        "CONJUNCTION REASON",
        "CONJUNCTION TIME"
    },
    {   // Prepositions
        "PREPOSITION UNKNOWN"
    },
    {   // Pronouns
        "PRONOUN UNKNOWN"
    }
};

string sort(char* word)
{
    // turn the word into uppercase for easier sorting
    word = toUpper(word);

    // try to find the sub-category of the word assuming it is a noun
    if (findInDictionary("me/noun/act.text",word))              { return words[1][1];   }
    if (findInDictionary("me/noun/animal.text",word))           { return words[1][2];   }
    if (findInDictionary("me/noun/artifact.text",word))         { return words[1][3];   }
    if (findInDictionary("me/noun/attribute.text",word))        { return words[1][4];   }
    if (findInDictionary("me/noun/body.text",word))             { return words[1][5];   }
    if (findInDictionary("me/noun/cognition.text",word))        { return words[1][6];   }
    if (findInDictionary("me/noun/communication.text",word))    { return words[1][7];   }
    if (findInDictionary("me/noun/event.text",word))            { return words[1][8];   }
    if (findInDictionary("me/noun/feeling.text",word))          { return words[1][9];   }
    if (findInDictionary("me/noun/food.text",word))             { return words[1][10];  }
    if (findInDictionary("me/noun/group.text",word))            { return words[1][11];  }
    if (findInDictionary("me/noun/location.text",word))         { return words[1][12];  }
    if (findInDictionary("me/noun/motive.text",word))           { return words[1][13];  }
    if (findInDictionary("me/noun/object.text",word))           { return words[1][14];  }
    if (findInDictionary("me/noun/person.text",word))           { return words[1][15];  }
    if (findInDictionary("me/noun/quantity.text",word))         { return words[1][16];  }
    if (findInDictionary("me/noun/relation.text",word))         { return words[1][17];  }
    if (findInDictionary("me/noun/shape.text",word))            { return words[1][18];  }
    if (findInDictionary("me/noun/state.text",word))            { return words[1][19];  }
    if (findInDictionary("me/noun/substance.text",word))        { return words[1][20];  }
    if (findInDictionary("me/noun/tops.text",word))             { return words[1][21];  }

    // try to find the sub-category of the word if we assume it to be a verb
    if (findInDictionary("me/verb/body.text",word))             { return words[2][1];   }
    if (findInDictionary("me/verb/change.text",word))           { return words[2][2];   }
    if (findInDictionary("me/verb/cognition.text",word))        { return words[2][3];   }
    if (findInDictionary("me/verb/communication.text",word))    { return words[2][4];   }
    if (findInDictionary("me/verb/competition.text",word))      { return words[2][5];   }
    if (findInDictionary("me/verb/consumption.text",word))      { return words[2][6];   }
    if (findInDictionary("me/verb/contact.text",word))          { return words[2][7];   }
    if (findInDictionary("me/verb/creation.text",word))         { return words[2][8];   }
    if (findInDictionary("me/verb/emotion.text",word))          { return words[2][9];   }
    if (findInDictionary("me/verb/framestext.text",word))       { return words[2][10];  }
    if (findInDictionary("me/verb/motion.text",word))           { return words[2][11];  }
    if (findInDictionary("me/verb/perception.text",word))       { return words[2][12];  }
    if (findInDictionary("me/verb/possession.text",word))       { return words[2][13];  }
    if (findInDictionary("me/verb/social.text",word))           { return words[2][14];  }
    if (findInDictionary("me/verb/stative.text",word))          { return words[2][15];  }
    if (findInDictionary("me/verb/weather.text",word))          { return words[2][16];  }

    // search for the word in all our conjunction lists
    if (findInDictionary("me/conj/comparison.text",word))       { return words[5][1];   }
    if (findInDictionary("me/conj/concession.text",word))       { return words[5][2];   }
    if (findInDictionary("me/conj/condition.text",word))        { return words[5][3];   }
    if (findInDictionary("me/conj/coordinating.text",word))     { return words[5][4];   }
    if (findInDictionary("me/conj/manner.text",word))           { return words[5][5];   }
    if (findInDictionary("me/conj/place.text",word))            { return words[5][6];   }
    if (findInDictionary("me/conj/reason.text",word))           { return words[5][7];   }\
    if (findInDictionary("me/conj/time.text",word))             { return words[5][0];   }

    // if the word is not found in any sub category then look in the main lists here
    if (findInDictionary("me/noun/noun1.text",word))            { return words[1][0];   }
    if (findInDictionary("me/noun/noun2.text",word))            { return words[1][0];   }
    if (findInDictionary("me/noun/noun3.text",word))            { return words[1][0];   }
    if (findInDictionary("me/verb/verb.text",word))             { return words[2][0];   }
    if (findInDictionary("me/adj/adj.text",word))               { return words[3][0];   }
    if (findInDictionary("me/adv/adv.text",word))               { return words[4][0];   }
    if (findInDictionary("me/conj/conj.text",word))             { return words[5][0];   }

    return words[0][0];
}
