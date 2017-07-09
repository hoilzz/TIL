import React, { Component } from 'react';
import PropTypes from 'prop-types';

const ObjectiveEx = ({option, answerId, onUpdateSelection, isEtc}) => {

    const onClick = (optionId, answerId, onUpdateSelection) => {
        onUpdateSelection({optionId, answerId});
    }

    const makeId = (id) => {
        return "ex"+id
    }

    const handleChange = (optionId, event) => {
        this['radioInput'+optionId].click();
        let etcValue = event.target.value.trim();
        onUpdateSelection({optionId, answerId, etcValue});
    }

    const etcText = () => {
        if(isEtc){
            return (
                <input
                    type = "text" 
                    id = {makeId(option.id)}
                    onChange = {event => handleChange(option.id, event)}
                    />
            )
        }
    }

    const setRefToRadio = (self, input) => {
        if(isEtc){
            self["radioInput"+option.id] = input
        }
    }
    
    return (
        <div>
            <input 
                ref = {input => {setRefToRadio(this, input, option.id)}}
                onClick={event => onClick(option.id, answerId ,onUpdateSelection)} 
                name={"objective"}
                id={makeId(option.id)} 
                type="radio"
                />
            <label htmlFor={makeId(option.id)}>{option.title}</label>
            {etcText()}
        </div>
    );
}

ObjectiveEx.propTypes = {
    answerId: Number,
    optionId: Number,
    onUpdateSelection: PropTypes.func,
};

ObjectiveEx.defaultProps = {
    answerId: 0,
    optionId: 0,
    onUpdateSelection: function(){console.warn('onUpdateSelection not defined')}
}

export default ObjectiveEx;